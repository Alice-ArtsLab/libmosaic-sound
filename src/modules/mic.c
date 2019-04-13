#include "include/mic.h"
#include <math.h>
#include <portaudio.h>
#include <stdio.h>
#include <stdlib.h>

mscsound_mic_t *mscsound_create_mic(int framesPerBuffer) {
  mscsound_mic_t *mic = malloc(sizeof(mscsound_mic_t));
  mic->framesPerBuffer = framesPerBuffer;
  mic->output0 = malloc(framesPerBuffer * sizeof(float));
  mic->process = mscsound_mic_process;

  return mic;
}

void mscsound_mic_process(mscsound_mic_t *mic, float *input) {
  for (int i = 0; i < mic->framesPerBuffer; i++) {
    mic->output0[i] = input[i];
  }
}
