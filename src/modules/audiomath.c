#include "include/audiomath.h"
#include <stdio.h>
#include <stdlib.h>

mscsound_math_t *mscsound_create_math(int framesPerBuffer,
                                            void(*function)) {
  mscsound_math_t *math = malloc(sizeof(mscsound_math_t));
  math->process = function;
  math->framesPerBuffer = framesPerBuffer;
  math->output0 = math->input0;

  return math;
}

void mscsound_add_2freq(mscsound_math_t *self) {
  for (int i = 0; i < self->framesPerBuffer; i++) {
    self->output0[i] = self->input0[i] + self->input1[i];
  }
}
void mscsound_sub_2freq(mscsound_math_t *self) {
  for (int i = 0; i < self->framesPerBuffer; i++) {
    self->output0[i] = self->input0[i] - self->input1[i];
  }
}
void mscsound_mul_2freq(mscsound_math_t *self) {
  for (int i = 0; i < self->framesPerBuffer; i++) {
    self->output0[i] = self->input0[i] * self->input1[i];
  }
}
void mscsound_div_2freq(mscsound_math_t *self) {
  for (int i = 0; i < self->framesPerBuffer; i++) {
    self->output0[i] = self->input0[i] / self->input1[i];
  }
}

void mscsound_add_freq_float(mscsound_math_t *self) {
  for (int i = 0; i < self->framesPerBuffer; i++) {
    self->output0[i] = self->input0[i] + *(self->input1);
  }
}
void mscsound_sub_freq_float(mscsound_math_t *self) {
  for (int i = 0; i < self->framesPerBuffer; i++) {
    self->output0[i] = self->input0[i] - *(self->input1);
  }
}
void mscsound_mul_freq_float(mscsound_math_t *self) {
  for (int i = 0; i < self->framesPerBuffer; i++) {
    self->output0[i] = self->input0[i] * *(self->input1);
  }
}
void mscsound_div_freq_float(mscsound_math_t *self) {
  for (int i = 0; i < self->framesPerBuffer; i++) {
    self->output0[i] = self->input0[i] / *(self->input1);
  }
}
