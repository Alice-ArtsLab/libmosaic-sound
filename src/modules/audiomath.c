#include <stdio.h>
#include <stdlib.h>
#include "include/audiomath.h"

mosaicsound_math_t *mosaicsound_create_math(int framesPerBuffer,
                                            void(*function)) {
  mosaicsound_math_t *math = malloc(sizeof(mosaicsound_math_t));
  math->process = function;
  math->framesPerBuffer = framesPerBuffer;
  math->output = malloc(framesPerBuffer * sizeof(float));

  return math;
}

void mosaicsound_add_2freq(mosaicsound_math_t *self) {
  for (int i = 0; i < self->framesPerBuffer; i++) {
    self->output[i] = self->input1[i] + self->input2[i];
  }
}
void mosaicsound_sub_2freq(mosaicsound_math_t *self) {
  for (int i = 0; i < self->framesPerBuffer; i++) {
    self->output[i] = self->input1[i] - self->input2[i];
  }
}
void mosaicsound_mul_2freq(mosaicsound_math_t *self) {
  for (int i = 0; i < self->framesPerBuffer; i++) {
    self->output[i] = self->input1[i] * self->input2[i];
  }
}
void mosaicsound_div_2freq(mosaicsound_math_t *self) {
  for (int i = 0; i < self->framesPerBuffer; i++) {
    self->output[i] = self->input1[i] / self->input2[i];
  }
}

void mosaicsound_add_freq_float(mosaicsound_math_t *self) {
  for (int i = 0; i < self->framesPerBuffer; i++) {
    self->output[i] = self->input1[i] + *(self->input2);
  }
}
void mosaicsound_sub_freq_float(mosaicsound_math_t *self) {
  for (int i = 0; i < self->framesPerBuffer; i++) {
    self->output[i] = self->input1[i] - *(self->input2);
  }
}
void mosaicsound_mul_freq_float(mosaicsound_math_t *self) {
  for (int i = 0; i < self->framesPerBuffer; i++) {
    self->output[i] = self->input1[i] * *(self->input2);
  }
}
void mosaicsound_div_freq_float(mosaicsound_math_t *self) {
  for (int i = 0; i < self->framesPerBuffer; i++) {
    self->output[i] = self->input1[i] / *(self->input2);
  }
}
