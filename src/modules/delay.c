#include "include/delay.h"
#include <math.h>
#include <portaudio.h>
#include <stdlib.h>
#include <string.h>

mscsound_delay_t *mscsound_create_delay(float time, int framesPerBuffer,
                                        int sampleRate) {
  mscsound_delay_t *delay = malloc(sizeof(mscsound_delay_t));
  int bufferSize = ceil(((sampleRate * time) / (float)1000) / framesPerBuffer) *
                   framesPerBuffer;

  bufferSize += 2 * framesPerBuffer;
  delay->bufferSize = bufferSize;
  delay->buffer = calloc(bufferSize, sizeof(float));
  delay->startWrite = round((sampleRate * time) / (float)1000);
  delay->startRead = 0;
  delay->output0 = malloc(sizeof(float *));
  (delay->output0)[0] = malloc(sizeof(float) * framesPerBuffer);
  delay->framesPerBuffer = framesPerBuffer;
  delay->sampleRate = sampleRate;
  delay->time = malloc(sizeof(float));
  *(delay->time) = time;
  delay->process = mscsound_delay_process;
  return delay;
}

void mscsound_delay_process(mscsound_delay_t **self) {
  for (int i = 0; i < (*self)->framesPerBuffer; i++) {
    (*self)->buffer[(*self)->startWrite] = (*((*self)->input0))[i];
    (*self)->startWrite = ((*self)->startWrite + 1) % ((*self)->bufferSize - 1);

    (*((*self)->output0))[i] = (*self)->buffer[(*self)->startRead];
    (*self)->startRead = ((*self)->startRead + 1) % ((*self)->bufferSize - 1);
  }
}
