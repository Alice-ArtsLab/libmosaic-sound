#include <stdio.h>
#include <stdlib.h>
#include "include/audiomath.h"

math_t *create_math(int framesPerBuffer, void(*function)) {
  math_t *math = malloc(sizeof(math_t));
  math->process = function;
  math->framesPerBuffer = framesPerBuffer;
  math->output = malloc(framesPerBuffer * sizeof(float));

  return math;
}

void add_2freq(math_t *self) {
  for (int i = 0; i < self->framesPerBuffer; i++) {
    self->output[i] = self->input1[i] + self->input2[i];
  }
}
void sub_2freq(math_t *self) {
  for (int i = 0; i < self->framesPerBuffer; i++) {
    self->output[i] = self->input1[i] - self->input2[i];
  }
}
void mul_2freq(math_t *self) {
  for (int i = 0; i < self->framesPerBuffer; i++) {
    self->output[i] = self->input1[i] * self->input2[i];
  }
}
void div_2freq(math_t *self) {
  for (int i = 0; i < self->framesPerBuffer; i++) {
    self->output[i] = self->input1[i] / self->input2[i];
  }
}

void add_freq_float(math_t *self) {
  for (int i = 0; i < self->framesPerBuffer; i++) {
    self->output[i] = self->input1[i] + *(self->input2);
  }
}
void sub_freq_float(math_t *self) {
  for (int i = 0; i < self->framesPerBuffer; i++) {
    self->output[i] = self->input1[i] - *(self->input2);
  }
}
void mul_freq_float(math_t *self) {
  for (int i = 0; i < self->framesPerBuffer; i++) {
    self->output[i] = self->input1[i] * *(self->input2);
  }
}
void div_freq_float(math_t *self) {
  for (int i = 0; i < self->framesPerBuffer; i++) {
    self->output[i] = self->input1[i] / *(self->input2);
  }
}
