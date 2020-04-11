/*
  Author : Mikael Troedsson

	For requirement see file ./../req/main.req
​
*/
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <ctype.h>
/* Req#1
Main program shall use shared library
.1 libresistance.so
.2 libpower.so
.3 libcomponent.so
*/
#include "./usr/bin/libcomponent.so/component.h"
#include "./usr/bin/libpower.so/power.h"
#include "./usr/bin/libresistance.so/resistance.h"
​
​
/* Req#2
Main program shall prompt user to enter
.1 voltage
.2 serie or parallell conection
.3 number of resistors used
.4 value of each used resistor
*/
float vIn;
char conType;
int nmbRstr;
float userFloatInput;
int oneMoreTime;
​
​
/* clear buffer from \n and EOF after scanf */
void clearBuff(){
	int j;
	while ( (j = getchar()) != '\n' && j != EOF )
		;
}
​
​
void userInput(float *p){

/* Req#2.1 get voltage from user*/
	oneMoreTime = 1;
	while(oneMoreTime){
		printf("Voltage ? ");
		scanf("%f", &vIn);
​
		if(vIn > 0.0 && vIn < 1000.0){
			oneMoreTime = 0;
		}
		else{
			printf("Voltage out of range.\nMust be more than 0 and less than 1000 Volt.\n");
			clearBuff();
		}
	}

/* Req#2.2 get connection type from user*/
	clearBuff();
	oneMoreTime = 1;
	while(oneMoreTime){
		printf("Type of connection (S/P) ? ");
		scanf("%c", &conType);
		conType = toupper(conType);

		if(conType == 'S' || conType == 'P'){
			oneMoreTime = 0;
		}
		else{
			printf("Unknown type\n");
			clearBuff();
		}
	}

/* Req#2.3 get number of resistors used from user */
	clearBuff();
	oneMoreTime = 1;
	while(oneMoreTime){
		printf("Number of resistors to connect ? ");
		scanf("%d", &nmbRstr);

		if(nmbRstr > 0 && nmbRstr < 4){
			oneMoreTime = 0;
		}
		else{
			printf("Invalid number.\nMust be more than 0 and less than 4.\n");
			clearBuff();
		}
	}


/* Req#2.4 get resistor values from user */
	p = realloc(p, nmbRstr * sizeof(float));
	for(int i=0; i < nmbRstr; i++){
 		oneMoreTime = 1;
		while(oneMoreTime){
			printf("Enter R%d ", i+1);
			scanf("%f", &userFloatInput);

			if(userFloatInput > 0){
				oneMoreTime = 0;
				p[i] = userFloatInput;
			}
			else{
				printf("Invalid resistance.\nMust be more than 0 Ohm\n");
				clearBuff();
			}
		}
	}
}
​
/*Req#3
Main program shall return to user
.1 total resistance of used resistors (float 1 decimal)
.2 total power (float 2 decimal)
.3 using E12 value, return replace resistors connected
   in serial, for total resistance entered ny user
*/
float resTotal;
float powTotal;
int nmbE12ForResTotal;
​
void mainOutput(float *p){
	printf("\n--==    result    ==--\n");
​
/* Req3.1 show total resistance calling shared library */
	resTotal = calc_resistance(nmbRstr, conType, p);
	printf("Rtot: \t%0.1f Ohm\n", resTotal);


/* Req3.2 show total power calling shared library */
	powTotal = calc_power_r(vIn, resTotal);
	printf("Ptot: \t%0.2f Watt\n", powTotal);
​
/* Req3.3 sho replaceing resistors calling shared library */
	float *res_Array = malloc(3 * sizeof(float));
	nmbE12ForResTotal = e_resistance(resTotal, res_Array );
​
	float newRtot = 0;
	printf("\nTo replace %0.1f Ohm, use in serie\n", resTotal);
	for(int i = 0; i < nmbE12ForResTotal; i++){
		printf("R%d: \t%0.1f Ohm\n", i + 1, res_Array[i]);
		newRtot += res_Array[i];
	}
	printf("New total resistance: %0.1f Ohm\n", newRtot);
	free(res_Array);
}
​
​
​
​
int main(int arc, char *argv[]){
	printf("--==  electrotest  ==--\n");

/* allocate memory for max numbers of resistors.
   reallocate in userInput when we know how many
   resistor used */
	float *pArrayRes = malloc(3 * sizeof(float));

/* ask user for input, pArrayRes will be filled with
   resistor values */
	userInput(pArrayRes);


/* show result using values from pArrayRes */
	mainOutput(pArrayRes);

/* free memory before exit program */
	free(pArrayRes);

	return 0;
}
