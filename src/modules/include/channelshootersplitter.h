#ifndef MSCSOUND_CHANNELSHOOTERSPLITTER_H
#define MSCSOUND_CHANNELSHOOTERSPLITTER_H

typedef struct {
  float *input0;
  float *output0;
  int framesPerBuffer;
  float sampleRate;
  void (*process)(void *self);
} mscsound_channelshootersplitter_t;

mscsound_channelshootersplitter_t *
mscsound_create_channelshootersplitter(int framesPerBuffer);
void mscsound_channelshootersplitter_process();

#endif /* channelshootersplitter.h */
