#include <math.h>
#include <portaudio.h>
#include <stdio.h>
#include <stdlib.h>
#include "include/speaker.h"

speaker_t *create_speaker(int framesPerBuffer) {
  speaker_t *speaker = malloc(sizeof(speaker_t));
  speaker->framesPerBuffer = framesPerBuffer;

  speaker->process = speaker_process;
  return speaker;
}

void speaker_process(speaker_t *speaker, float *output) {
  for (int i = 0; i < speaker->framesPerBuffer; i++) {
    output[i] = speaker->input[i];
  }
}
