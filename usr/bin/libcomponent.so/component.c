/*
	File	component.c
	Author	Mikael Thoresson, 2020

	Library for calculate resistors from E12 serie that connected in
	serie are equal to incomming resistance.
​
	Arguments
	orig_resistance		Resistance that shall be replaced.
	*res_array			Array of resistors that replaces orig_resistance.

	Return
	count				number of resistors needed to be equal to
						orig_resistance.

	Requirements
	1. count shall NOT be less than 0 and NOT greater than 3.

	2. orig_resistance shall NOT be less than 0 Ohm and NOT greater than 10 M Ohm
	   On no valid range, return -1.

	3. Array res_array shall contain needed resistances for orig_resistance.
	   Unused places in array shall contain 0.
	   On Null pointer to array, return -2.

	4. Range of values in E12 serie shall be 1.0 to 10 M Ohm

		  	
*/
​
#include <stddef.h>
#include <stdio.h>
​
int init_component(void){
	return 0;
}
​
int e_resistance(float orig_resistance, float *res_array ){
​
/* req #3 */
if(res_array == NULL)
	return -2;
​
/* req#3 */
for(int i = 0; i < 3; i++)
	res_array[i] = 0;
​
​
/* req #2 */
if(orig_resistance < 0 || orig_resistance > 10000000)
	return -1;
​
​
/*
    Req #4
	Make array of E12 resistors 0 - 10M Ohm
*/
int nmbOfE12 = (12 * 7) + 1;
​
float E12base[] = { 1.0, 1.2, 1.5, 1.8, 2.2, 2.7, 3.3, 3.9, 4.7, 5.6, 6.8, 8.2 };
float times[] = { 1, 10, 100, 1000, 10000, 100000, 1000000 };
float E12[nmbOfE12];
​
int k = 0;
​
for(int i = 0; i < 7; i++){
	for(int j = 0; j < 12; j++){
		E12[k] = E12base[j] * times[i];
		k++;
	}
}
E12[k] = 10000000;
​

/* req #1 */
int count = 0;
float rTot = 0;
int j;
int exit;
​
/*
Find replacing resistors
Go through the list of E12 and compare with orig_resistance.
When E12 resistor is greater than orig_resistance, save previous E12 in array and add it to rTot.
Start all over again now compare E12 + rTot with orig_resistance.
​
When the first E12 (j = 0) makes E12 + rTot > orig_resistance it means that there are no more
resistors to add in the array.
*/
​
for(int i = 0; i < 3; i++){
	j = 0;
	exit = 0;

	while( (exit == 0) && (j < nmbOfE12) ){

		if( E12[j] + rTot > orig_resistance ){
			if( j > 0){
				/* printf("Found R: %0.2f\n", E12[j-1]); */
				rTot += E12[j-1];
				res_array[count] = E12[j-1];
				count++;
				exit = 1;
			}
			else{
				/* printf("Add nothing\n"); */
				exit = 1;
			}
		}
	j++;
	}
	/* printf("Rtot: %0.2f\n", rTot); */
}
​
​
return count;
}
