#include <math.h>
#include <portaudio.h>
#include <stdio.h>
#include <stdlib.h>
#include "include/mic.h"

mic_t *create_mic(int framesPerBuffer) {
  mic_t *mic = malloc(sizeof(mic_t));
  mic->framesPerBuffer = framesPerBuffer;
  mic->output = malloc(framesPerBuffer * sizeof(float));
  mic->process = mic_process;

  return mic;
}

void mic_process(mic_t *mic, float *input) {
  for (int i = 0; i < mic->framesPerBuffer; i++) {
    mic->output[i] = input[i];
  }
}
