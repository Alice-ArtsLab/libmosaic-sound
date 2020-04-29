#ifndef MSCSOUND_SPEAKER_H
#define MSCSOUND_SPEAKER_H
typedef struct {
  float **input0;
  int framesPerBuffer;
  void (*process)(void *self, float **output);
} mscsound_speaker_t;

mscsound_speaker_t *mscsound_create_speaker(int framesPerBuffer);
void mscsound_speaker_process();
#endif /* speaker.h */
