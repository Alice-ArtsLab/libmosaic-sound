#include <math.h>
#include <portaudio.h>
#include <stdio.h>
#include <stdlib.h>
#include "include/speaker.h"

mosaicsound_speaker_t *mosaicsound_create_speaker(int framesPerBuffer) {
  mosaicsound_speaker_t *speaker = malloc(sizeof(mosaicsound_speaker_t));
  speaker->framesPerBuffer = framesPerBuffer;

  speaker->process = mosaicsound_speaker_process;
  return speaker;
}

void mosaicsound_speaker_process(mosaicsound_speaker_t *speaker,
                                 float *output) {
  for (int i = 0; i < speaker->framesPerBuffer; i++) {
    output[i] = speaker->input0[i];
  }
}
