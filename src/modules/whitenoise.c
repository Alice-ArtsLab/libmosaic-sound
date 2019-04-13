#include "include/whitenoise.h"
#include <math.h>
#include <stdlib.h>

mscsound_noise_t *mscsound_create_noise(int framesPerBuffer) {
  mscsound_noise_t *noise = malloc(sizeof(mscsound_noise_t));
  noise->output0 = malloc(sizeof(float) * framesPerBuffer);
  noise->process = mscsound_noise_process;
  noise->framesPerBuffer = framesPerBuffer;

  return noise;
}

void mscsound_noise_process(mscsound_noise_t *noise) {
  for (int i = 0; i < noise->framesPerBuffer; i++) {
    noise->output0[i] = sin(rand() % 20001);
  }
}
