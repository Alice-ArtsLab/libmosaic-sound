#include "include/speaker.h"
#include <math.h>
#include <portaudio.h>
#include <stdio.h>
#include <stdlib.h>

mscsound_speaker_t *mscsound_create_speaker(int framesPerBuffer) {
  mscsound_speaker_t *speaker = malloc(sizeof(mscsound_speaker_t));
  speaker->framesPerBuffer = framesPerBuffer;

  speaker->process = mscsound_speaker_process;
  return speaker;
}

void mscsound_speaker_process(mscsound_speaker_t **self,
                                 float **output) {
  for (int i = 0; i < (*self)->framesPerBuffer; i++) {
    (*output)[i] = (*((*self)->input0))[i];
  }
}
