#include "include/audiomath.h"
#include <stdio.h>
#include <stdlib.h>

mscsound_audiomath_t *mscsound_create_audiomath(int framesPerBuffer, void(*function)) {
  mscsound_audiomath_t *math = malloc(sizeof(mscsound_audiomath_t));
  math->output0 = calloc(1, sizeof(float*));
  math->process = function;
  math->framesPerBuffer = framesPerBuffer;

  return math;
}

void mscsound_add_2freq(mscsound_audiomath_t **self) {
  *((*self)->output0) = *((*self)->input0);
  for (int i = 0; i < (*self)->framesPerBuffer; i++) {
    (*((*self)->output0))[i] = (*((*self)->input0))[i] + (*((*self)->input1))[i];
  }
}
void mscsound_sub_2freq(mscsound_audiomath_t **self) {
  *((*self)->output0) = *((*self)->input0);
  for (int i = 0; i < (*self)->framesPerBuffer; i++) {
    (*((*self)->output0))[i] = (*((*self)->input0))[i] - (*((*self)->input1))[i];
  }
}
void mscsound_mul_2freq(mscsound_audiomath_t **self) {
  *((*self)->output0) = *((*self)->input0);
  for (int i = 0; i < (*self)->framesPerBuffer; i++) {
    (*((*self)->output0))[i] = (*((*self)->input0))[i] * (*((*self)->input1))[i];
  }
}
void mscsound_div_2freq(mscsound_audiomath_t **self) {
  *((*self)->output0) = *((*self)->input0);
  for (int i = 0; i < (*self)->framesPerBuffer; i++) {
    (*((*self)->output0))[i] = (*((*self)->input0))[i] / (*((*self)->input1))[i];
  }
}
