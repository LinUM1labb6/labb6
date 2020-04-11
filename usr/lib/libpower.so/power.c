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