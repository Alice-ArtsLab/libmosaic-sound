#ifndef mscsound_SPEAKER_H
#define mscsound_SPEAKER_H
typedef struct {
  float *input0;
  int framesPerBuffer;
  void (*process)(void *self, float *);
} mscsound_speaker_t;

mscsound_speaker_t *mscsound_create_speaker(int framesPerBuffer);
void mscsound_speaker_process();
#endif /* speaker.h */
