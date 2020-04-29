#include "include/whitenoise.h"
#include <math.h>
#include <stdlib.h>

mscsound_noise_t *mscsound_create_noise(int framesPerBuffer) {
  mscsound_noise_t *noise = malloc(sizeof(mscsound_noise_t));
  noise->output0 = malloc(sizeof(float*));
  noise->output0[0] = malloc(sizeof(float) * framesPerBuffer);
  noise->process = mscsound_noise_process;
  noise->framesPerBuffer = framesPerBuffer;

  return noise;
}

void mscsound_noise_process(mscsound_noise_t **self) {
  for (int i = 0; i < (*self)->framesPerBuffer; i++) {
    (*((*self)->output0))[i] = sin(rand() % 20001);
  }
}
