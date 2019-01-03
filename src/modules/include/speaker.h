#ifndef MOSAICSOUND_SPEAKER_H
#define MOSAICSOUND_SPEAKER_H
typedef struct {
  float *input0;
  int framesPerBuffer;
  void (*process)(void *self, float *);
} mosaicsound_speaker_t;

mosaicsound_speaker_t *mosaicsound_create_speaker(int framesPerBuffer);
void mosaicsound_speaker_process();
#endif /* speaker.h */
