#include <math.h>
#include <stdlib.h>
#include "include/whitenoise.h"

noise_t* create_noise(int framesPerBuffer) {
  noise_t* noise = malloc(sizeof(noise_t));
  noise->output = malloc(sizeof(float) * framesPerBuffer);
  noise->process = noise_process;
  noise->framesPerBuffer = framesPerBuffer;

  return noise;
}

void noise_process(noise_t* noise) {
  for (int i = 0; i < noise->framesPerBuffer; i++) {
    noise->output[i] = sin(rand() % 20001);
  }
}
