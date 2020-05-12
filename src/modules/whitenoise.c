#include "include/whitenoise.h"
#include <math.h>
#include <stdlib.h>

mscsound_whitenoise_t *mscsound_create_whitenoise(int framesPerBuffer) {
  mscsound_whitenoise_t *noise = malloc(sizeof(mscsound_whitenoise_t));
  noise->output0 = malloc(sizeof(float *));
  noise->output0[0] = malloc(sizeof(float) * framesPerBuffer);
  noise->process = mscsound_whitenoise_process;
  noise->framesPerBuffer = framesPerBuffer;

  return noise;
}

void mscsound_whitenoise_process(mscsound_whitenoise_t **self) {
  for (int i = 0; i < (*self)->framesPerBuffer; i++) {
    (*((*self)->output0))[i] = sin(rand() % 20001);
  }
}
