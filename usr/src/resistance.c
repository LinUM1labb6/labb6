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
