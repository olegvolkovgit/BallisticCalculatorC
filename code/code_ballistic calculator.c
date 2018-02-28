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
	int distance; //distance (in meters)
	float heith; // object heith
	int thousands; // thousands
	int targ_speed; // target speed (meters per second)
	int angle; // angle of movement
} S; 
struct  S_DATA *S_ptr=&S;
struct T_DATA 
{
	int temperature; // T(celcium)
	int side_wind; // wind speed (meters per second)
	int angle_wind; // angle of wind blowing (degrees)

} T;
struct  T_DATA *T_ptr=&T;

char*naming()// dynamic memory allocation of shooter and file's names
{
	char* n_ptr = NULL;
	int i=0;
	char symbol;
	
	n_ptr = (char*)malloc(hundred * sizeof(char));
	printf("enter your name and callsign via '_': ");
    scanf("%s",n_ptr);
    strcat(n_ptr,".txt");
	n_ptr=(char*)realloc(n_ptr,strlen(n_ptr)+1);
	return n_ptr;
}

void collect_S_DATA (struct S_DATA *S_ptr) // collecting DATA for shooting
{
	printf("set distance ");
	scanf("%d",&S_ptr->distance);
	printf("set object heith ");
	scanf("%g", &S_ptr->heith);
	printf("set thousands ");
	scanf("%d", &S_ptr->thousands);
	printf("set target speed meters per second ");
	scanf("%d", &S_ptr->targ_speed);
	printf("set angle of movement ");
	scanf("%d", &S_ptr->angle);
}
void collect_T_DATA(struct T_DATA *T_ptr) // collecting DATA of weather
{
	printf("set temperature: ");
	scanf("%d", &T_ptr->temperature);
	printf("set wind speed: ");
	scanf("%d", &T_ptr->side_wind);
	printf("set wind angle: ");
	scanf("%d", &T_ptr->angle_wind);
}
float derevation(struct S_DATA *S_ptr )
{
	float side;
	if (S_ptr->distance >= 700)
	{
		printf("derevation overflow!\nset aiming point\n");
		side = half;
		printf("side to left in %g figures\n", side);
	}
	if (S_ptr->distance >= thousand)
	{
		printf("derevation overflow!\nset aiming point\n");
		side = 1;
		printf("side to left in %g figures\n", side);
	}

	return side;
}
void report(char *n_ptr, struct S_DATA *S_ptr, struct T_DATA *T_ptr)
{//createing reporting file named as shooter is
	FILE *file;
	file=fopen(n_ptr, "w"); 
	if (!file)
	{
		printf("ERROR file opening\n");
	}
	else
	{
		fprintf(file, "ENTERED CORRECTIONS:");
		fprintf(file, "\n\n");
		fprintf(file, "temperature: %d\n",T_ptr->temperature);
		fprintf(file, "side wind: %d\n",T_ptr->side_wind);
		fprintf(file, "wind angle: %d",T_ptr->angle_wind);
		fprintf(file,"\n\n");
		fprintf(file, "distance to target: %d\n",S_ptr->distance);
		fprintf(file, "heith of target: %g\n",S_ptr->heith);
		fprintf(file, "thousands: %d\n",S_ptr->thousands);
		fprintf(file, "speed of target: %d\n",S_ptr->targ_speed);
		fprintf(file, "angle of target movement: %d\n",S_ptr->angle);
		fclose(file);
	    printf("\nreporting file was made\n");
	}
}
float DUJ(struct S_DATA *S_ptr, struct T_DATA *T_ptr) // thousand's formula
{
	float parametr;
	printf("1-distance;\n2-target heith;\n3-thousands ");
	scanf("%g",&parametr);
	if (parametr == 1) 
	{ 
		parametr = (((S_ptr->heith * thousand) / S_ptr->thousands)); 
		printf("needed parametr - %g\nAIM is - %g\n",parametr,(parametr/hundred));
	}
	if (parametr == 2) 
	{ 
		parametr = ((S_ptr->distance * S_ptr->thousands) / thousand);
		printf("needed parametr - %g\n", parametr);
	}
	if (parametr == 3) 
	{
		parametr = ((S_ptr->heith * thousand) / S_ptr->distance);
		printf("needed parametr - %g\n", parametr);
	}
	return parametr;
}
float T_move(struct S_DATA *S_ptr, struct T_DATA *T_ptr) //movement correction of AIMing point in figures
{
	float figures;
	printf("side AIMING POINT forward target movement ");
	if (S_ptr->distance < 500 && S_ptr->angle == 45)
	{
		figures = (S_ptr->distance / hundred) - half;
		figures/=2;
	}
	if (S_ptr->distance < 500)
	{
		figures = (S_ptr->distance / hundred) - half;
	}
	else
	{
		figures = S_ptr->distance / hundred;
	}
	printf("for %f figures\n", figures);
	return figures;
}
float S_wind(struct S_DATA *S_ptr, struct T_DATA *T_ptr) //side wind correction of AIMing point in figures
{
	float figures;
	printf("side AIMING POINT up the wind ");
	if (T_ptr->side_wind == 2)	figures =  (S_ptr->distance / hundred) - twoo;
	if (T_ptr->side_wind == 4)  figures = ((S_ptr->distance / hundred) - twoo) / twoo;
	if (T_ptr->side_wind == 8)	figures = ((S_ptr->distance / hundred) - twoo) / four;
	
	if (T_ptr->side_wind == 2 && T_ptr->angle_wind ==45)	figures = (((S_ptr->distance / hundred) - twoo) / four)/twoo;
	if (T_ptr->side_wind == 4 && T_ptr->angle_wind ==45)	figures = (((S_ptr->distance / hundred) - twoo) / four)/twoo;
	if (T_ptr->side_wind == 8 && T_ptr->angle_wind ==45)	figures = (((S_ptr->distance / hundred) - twoo) / four)/twoo;
	printf("in %d figures\n",figures);
	return figures;
}
over_excessing(struct S_DATA *S_ptr)
{
  int d_Aim;
  int arr[8][15];
  printf("\ndistance to target: %d", S_ptr->distance);
  int dis = S_ptr->distance/hundred;
  printf("\nenter fixed aiming distance of your sight: ");
  scanf("%d",&d_Aim);
  
  arr[0][0] = 1; arr[0][1] = 1; arr[0][2] = 6; arr[0][3] = 11; arr[0][4] = 18;
  arr[1][0] = 0; arr[1][1] = 5; arr[1][2] = 14;arr[1][3] = 25; arr[1][4] = 38;
  arr[1][5] = 53;arr[1][6] = 67;arr[1][7] = 79;arr[1][8] = 127;
  arr[2][0] = -3;arr[2][1] = 4; arr[2][2] = 18;arr[2][3] = 35; arr[2][4] = 53;
  arr[3][1] = 0; arr[3][2] = 17;arr[3][3] = 39;arr[3][4] = 64; arr[3][5] = 95; 
  arr[3][6] =135;arr[3][7] =169;arr[3][8] =271;
  arr[4][1] =-11;arr[4][2] = 11;arr[4][3] = 39;arr[4][4] = 70;
  arr[5][2] = 0; arr[5][3] = 33;arr[5][4] = 70;arr[5][5] =120; arr[5][6] = 157;
  arr[5][7] =215;arr[5][8] =364;
  arr[6][2] =-18;arr[6][3] = 20;arr[6][4] = 64;
  arr[7][3] = 0; arr[7][4] = 50;arr[7][5] =110;arr[7][6] =159; arr[7][7] =254;
  arr[7][8] = 450;
  arr[8][3] =-28;arr[8][4] = 28;
  arr[9][4] = 0; arr[9][5] = 74; arr[9][6]=165;arr[9][7] = 265; 
  arr[9][8] = 500;
  arr[10][4] =-43;
  arr[11][5] = 0;arr[11][6]=115;arr[11][7]=230;arr[11][8] =540;
  arr[12][7] = 0;arr[12][8] =400;
  arr[13][8] = 260;
  arr[14][8] = 0;                   

  int dist = arr[d_Aim][dis];
  if(!dist)
  printf("\nanounced data has no practical meaning or does'nt exist");
  if(dist < 0)
  printf("\ndecreasing of trajectory! up to %d santemeters",dist);
  if(dist > 0)
  printf("\nexess sight is %d santemeters on the field",dist);
}
void main()
{
	char* name;
	int choise = 0;
	int excess;
	float sa;
	name = naming(); // dynamic naming
	collect_S_DATA(S_ptr); // 1-st structure 
	collect_T_DATA(T_ptr); // 2-nd structure
	report(name,S_ptr,T_ptr); // creating file
	free(name); // free name memory
	derevation(S_ptr); // report shooter about derevation
	do // make calculating of corrections
	{
		printf("chose needed items:\n1 - formula thousands\n2 - PSO-grid correction\n3 - exessing sight\n");
		scanf("%d",&choise);
		switch (choise)
		{
			case 1:
		    	DUJ(S_ptr,T_ptr);
				break;
			case 2:
				sa = T_move(S_ptr, T_ptr);
				S_wind(S_ptr, T_ptr);
				break;
			case 3:
			over_excessing(S_ptr);
		}
		fflush(stdin);
		printf("\n\nto quit press 'esc'\n");
	} while (_getch()!=27);
}
