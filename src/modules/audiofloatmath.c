#include "include/audiofloatmath.h"
#include <stdio.h>
#include <stdlib.h>

mscsound_audiofloatmath_t *mscsound_create_audiofloatmath(int framesPerBuffer, void(*function)) {
  mscsound_audiofloatmath_t *math = malloc(sizeof(mscsound_audiofloatmath_t));
  math->output0 = calloc(1, sizeof(float*));
  math->process = function;
  math->framesPerBuffer = framesPerBuffer;

  return math;
}

void mscsound_add_freq_float(mscsound_audiofloatmath_t **self) {
  *((*self)->output0) = *((*self)->input0);
  for (int i = 0; i < (*self)->framesPerBuffer; i++) {
    (*((*self)->output0))[i] = (*((*self)->input0))[i] + *((*self)->input1);
  }
}

void mscsound_sub_freq_float(mscsound_audiofloatmath_t **self) {
  *((*self)->output0) = *((*self)->input0);
  for (int i = 0; i < (*self)->framesPerBuffer; i++) {
    (*((*self)->output0))[i] = (*((*self)->input0))[i] - *((*self)->input1);
  }
}

void mscsound_mul_freq_float(mscsound_audiofloatmath_t **self) {
  *((*self)->output0) = *((*self)->input0);
  for (int i = 0; i < (*self)->framesPerBuffer; i++) {
    (*((*self)->output0))[i] = (*((*self)->input0))[i] * *((*self)->input1);
  }
}

void mscsound_div_freq_float(mscsound_audiofloatmath_t **self) {
  *((*self)->output0) = *((*self)->input0);
  for (int i = 0; i < (*self)->framesPerBuffer; i++) {
    (*((*self)->output0))[i] = (*((*self)->input0))[i] / *((*self)->input1);
  }
}
