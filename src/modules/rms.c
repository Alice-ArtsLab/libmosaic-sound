#include "include/rms.h"
#include <math.h>
#include <portaudio.h>
#include <stdlib.h>

mscsound_rms_t *mscsound_create_rms(int framesPerBuffer) {
  mscsound_rms_t *rms = malloc(sizeof(mscsound_rms_t));
  rms->output0 = calloc(1, sizeof(float));
  *(rms->output0) = 0;
  rms->framesPerBuffer = framesPerBuffer;
  rms->process = mscsound_rms_process;
  return rms;
}

void mscsound_rms_process(mscsound_rms_t **self) {
  float rms = 0;

  for (int i = 0; i < (*self)->framesPerBuffer; i++) {
    rms += pow((*((*self)->input0))[i], 2);
  }

  rms = sqrt(rms / (*self)->framesPerBuffer);

  *((*self)->output0) = (rms * 0.3) + (*((*self)->output0) * 0.7);
}
