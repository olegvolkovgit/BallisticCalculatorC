#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <conio.h>

#define NAME 50
#define twoo 2
#define four 4
#define hundred 100
#define thousand 1000
#define half 0.5

struct S_DATA 
{
	int distance =0; //distance (in meters)
	float heith =0; // object heith
	int thousands =0; // thousands
	int targ_speed =0; // target speed (meters per second)
	int angle=0; // angle of movement
}S; 
struct  S_DATA *S_ptr ; // покажчик для 
struct T_DATA 
{
	int temperature =0; // T(celcium)
	int side_wind =0; // wind speed (meters per second)
	int angle_wind =0; // angle of wind blowing (degrees)

}T;
struct  T_DATA *T_ptr ;

char* naming(); // dynamic naming
void collect_S_DATA(struct S_DATA *S_ptr); // 1-st structure 
void collect_T_DATA(struct T_DATA *T_ptr); // 2-nd structure
void report(char *n_ptr, struct S_DATA *S_ptr, struct T_DATA *T_ptr); // creating file
float derevation(struct S_DATA *S_ptr); // report shooter about derevation
float DUJ(struct S_DATA *S_ptr, struct T_DATA *T_ptr);
float T_move(struct S_DATA *S_ptr, struct T_DATA *T_ptr);
int S_wind(struct S_DATA *S_ptr, struct T_DATA *T_ptr);

void main(struct S_DATA *S_ptr, struct T_DATA *T_ptr)
{
	char* name;
	int choise = 0;
	float sa;
	name = naming(); // dynamic naming
	collect_S_DATA(S_ptr); // 1-st structure 
	collect_T_DATA(T_ptr); // 2-nd structure
	report(name,S_ptr,T_ptr); // creating file
	free(name); // free name memory
	derevation(S_ptr); // report shooter about derevation
	do // make calculating of corrections
	{
		printf("chose needed items: 1 - formula thousands.\n2 - PSO-grid correction.");
		scanf_s("%4d",&choise);
		switch (choise)
		{
		case 1:
		DUJ(S_ptr,T_ptr);
			break;
		case 2:
			sa = T_move(S_ptr, T_ptr);
			S_wind(S_ptr, T_ptr);
			break;
		}
	} while (_getch()!=27);

}

char*naming()// dynamic memory allocation of shooter and file's names
{
	char N[NAME];
	char* n_ptr;
	n_ptr = N;
	int i = 0;
	char symbol;
	printf("enter your name and callsign via '_':");
	do
	{
		n_ptr = (char*)malloc(1 * sizeof(char));
		n_ptr[i] = scanf_s("%c", &symbol, 1);
	} while (_getch() != 32);

	return n_ptr;
}

void collect_S_DATA(struct S_DATA *S_ptr) // collecting DATA for shooting
{
	printf("set distance");
	scanf_s("%16d", &S_ptr->distance);
	printf("set object heith");
	scanf_s("%8g", &S_ptr->heith);
	printf("set thousands");
	scanf_s("%8d", &S_ptr->thousands);
	printf("set target speed meters per second");
	scanf_s("%8d", &S_ptr->targ_speed);
	printf("set angle of movement");
	scanf_s("%8d", &S_ptr->angle);
}
void collect_T_DATA(struct T_DATA *T_ptr) // collecting DATA of weather
{
	printf("set temperature");
	scanf_s("%8d", &T_ptr->temperature);
	printf("set wind speed");
	scanf_s("%8d", &T_ptr->side_wind);
	printf("set wind angle");
	scanf_s("%8d", &T_ptr->angle_wind);
}
void report(char *n_ptr, struct S_DATA *S_ptr, struct T_DATA *T_ptr)
{//createing reporting file named as shooter is
	FILE *file;
	fopen_s(&file, n_ptr, "w");
	if ((fopen_s(&file, n_ptr, "w")) == NULL)
	{
		printf("ERROR file opening");
	}
	else
	{
		fprintf(file, "ENTERED CORRECTIONS:");
		fprintf(file, "\n\n");
		fwrite(&T, sizeof(&T_ptr), 1, file);
		fprintf(file, "\n\n");
		fwrite(&S, sizeof(&T_ptr), 1, file);
	}
	fclose(file);
	printf("reporting file was made");
}
float derevation(struct S_DATA *S_ptr)
{
	float side;
	if (S_ptr->distance >= 800)
	{
		printf("derevation overflow!\nset aiming point");
		side = half;
		printf("side to left in %g figures", side);
	}
	if (S_ptr->distance >= thousand)
	{
		printf("derevation overflow!\nset aiming point");
		side = 1;
		printf("side to left in %g figures", side);
	}

	return side;
}
float DUJ(struct S_DATA *S_ptr, struct T_DATA *T_ptr) // thousand's formula
{
	float parametr;
	printf("1-distance;2-target heith;3-thousands");
	scanf_s("%4g", &parametr);
	if (parametr == 1)
	{
		parametr = (float)(((S_ptr->heith * thousand) / S_ptr->thousands));
		printf("needed parametr - %g\nAIM is - %g", parametr, (parametr / hundred));
	}
	if (parametr == 2)
	{
		parametr = (float)((S_ptr->distance * S_ptr->thousands) / thousand);
		printf("needed parametr - %g", parametr);
	}
	if (parametr == 3)
	{
		parametr = (float)((S_ptr->heith * thousand) / S_ptr->distance);
		printf("needed parametr - %g", parametr);
	}
	return parametr;
}
float T_move(struct S_DATA *S_ptr, struct T_DATA *T_ptr) //movement correction of AIMing point in figures
{
	float figures;
	printf("side AIMING POINT forward target movement");
	if (S_ptr->distance < 500)
	{
		figures = (float)((S_ptr->distance / hundred) - half);
	}
	else
	{
		figures = (float)(S_ptr->distance / hundred);
	}
	printf("for %f figures", figures);
	return figures;
}
int S_wind(struct S_DATA *S_ptr, struct T_DATA *T_ptr) //side wind correction of AIMing point in figures
{
	int figures;
	printf("side AIMING POINT up the wind");
	if (T_ptr->side_wind == 2)	figures = (S_ptr->distance / hundred) - twoo;
	if (T_ptr->side_wind == 4)  figures = ((S_ptr->distance / hundred) - twoo) / twoo;
	if (T_ptr->side_wind == 8)	figures = ((S_ptr->distance / hundred) - twoo) / four;
	printf("in %d figures", figures);
	return figures;
}