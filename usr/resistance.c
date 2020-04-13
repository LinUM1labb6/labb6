/* 
  	Author : Monika Willman
 
	Function: calc_resistance(int count, char conn, float *array)

	Arguments:	(int) count
			Number of resistors in array that shall be used in 
			the calculation

			(char) conn
			Indicate serie or parallell (S, P) connections of resistors
			
			(float) *array
			Pointer to array with resistors for calculate total resistance

	Return		(float) total resistance
			or a value to indicate an error



	Requirements

	Req#1		count shall not be less than 0 and not greater than 3
			otherwise return -1

	Req#2		conn shall be 'P' or 'S'
			otherwise return -1
			
	Req#3		pointer *array shall not be empty
			otherwise return -2
			
	Req#4		if conn = P and any of the resistors in the calculation is = 0 Ohm
			then return 0
			
	Req#5		if not returning 0 or less
			calculate total resistance due to S or P and return value in float format
			

	Note		Req#3 is in original form, "library shall not crash". 
			Current req#3 adds a return value, and of course the library shall not crash.
*/
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <ctype.h>
#include <float.h>
#include <math.h>
#define sizeOfArray(x)  (sizeof(x) / sizeof((x)[0]))

float calc_resistance(int count, char conn, float *p) {
  if (count < 0 || count > 3) {
    return -1;
  }
  if (conn != 'S' && conn != 'P') {
    return -1;
  }
  if (p==NULL) {
    return -2;
  }
  if (conn == 'P') {
    for (int i=0; i < count; i++) {
      if (fabs(p[i] - 0.0f) <= FLT_EPSILON) {
        return 0;
      }
    }
  }

  float resistance = 0.0f;
  if (conn == 'S') {
    for (int i=0; i < count; i++) {
      resistance += p[i];
    }
  }
  else { /* conn == 'P' */
    float invertedResistance = 0.0f;
    for (int i=0; i < count; i++) {
      invertedResistance += 1/p[i];
    }
    resistance = 1/invertedResistance;
  }
  return resistance;
}
