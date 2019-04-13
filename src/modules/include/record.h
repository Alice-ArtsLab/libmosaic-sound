#ifndef mscsound_RECORD_H
#define mscsound_RECORD_H

typedef struct {
  int framesPerBuffer;
  int sampleRate;
  int paused; /* 0: paused ; 1: playing*/
  int time;
  int currentTime;
  int writeCount;
  float *input0;
  void *sf;
  void (*process)(void *self);
  char *filename;
} mscsound_record_t;

mscsound_record_t *mscsound_create_record(char *filename,
                                                int framesPerBuffer, int fTime,
                                                int sr);

void mscsound_record_process();
void mscsound_record_finished();

#endif /* record.h */
