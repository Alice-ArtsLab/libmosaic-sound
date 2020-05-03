#ifndef MSCSOUND_RECORD_H
#define MSCSOUND_RECORD_H

typedef struct {
  int framesPerBuffer;
  int sampleRate;
  char **paused; /* yes ; no*/
  char **stop; /* yes ; no*/
  int currentTime;
  int writeCount;
  float **input0;
  void *sf;
  void (*process)(void *self);
  char **filename;
} mscsound_record_t;

mscsound_record_t *mscsound_create_record(char *filename,
                                                int framesPerBuffer, int sr);

void mscsound_record_process();
void mscsound_record_finished();

#endif /* record.h */
