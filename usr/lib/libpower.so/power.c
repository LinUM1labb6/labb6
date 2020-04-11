/*
    File   power.c
    Author Lucas Sjöqvist, 2020

    Functions:	float calc_power_r(float volt, float resistance)
                float calc_power_i(float volt, float current)

    Arguments:	(float) volt
                Volt over the circuit

                (float) resistance
                Total resistance in circuit
                
                (float) current
                Incoming current in circuit

    Return:	    (float) Total power due to voltage
                (float) Total power due to current
                or a value to indicate an error
            
    Requirements
    Req#1	resistance shall not be less than 0
            otherwise return -1
                
    Req#2	resistance shall not be 0
            otherwise return -2
                
    Req#3	volt shall not be less than 0
            otherwise return -1
                
    Req#4	current shall not be less than 0
            otherwise return -1

    Req#5	if not returning less than 0
            calculate total power in circuit and return value in float format
                         
    Note	Req#1-5 are not included in the exercise but added for better performans
            and a more robust design to the library
			
*/

#include <stdio.h>
#include <math.h>

float calc_power_r(float volt, float resistance) 
{
    float effect;
    effect = pow(volt, 2) / resistance;
    // Float trunacating with int becaucse int dont round.
    int tmp = effect * 100;
    effect = tmp / 100.0;
    return effect;
}

float calc_power_i(float volt, float current) 
{
    float effect;
    effect = volt * current;
    // Float trunacating with int becaucse int dont round.
    int temp = effect * 100;
    effect = temp / 100.0;
    return effect;
}