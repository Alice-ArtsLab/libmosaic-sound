#include <sndfile.h>
#include <sndfile.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/record.h"

mosaicsound_record_t *mosaicsound_create_record(char *filename,
                                                int framesPerBuffer, int fTime,
                                                int sr) {
  mosaicsound_record_t *record = malloc(sizeof(mosaicsound_record_t));

  record->writeCount = 0;
  record->currentTime = 0;
  record->time = fTime;
  record->paused = 0;
  record->sampleRate = sr;
  record->framesPerBuffer = framesPerBuffer;
  record->filename = malloc(strlen(filename) + 1);
  strcpy(record->filename, filename);

  SF_INFO info;
  record->sf = (SNDFILE *)record->sf;
  info.samplerate = record->sampleRate;
  info.channels = 1;
  info.format = SF_FORMAT_WAV | SF_FORMAT_FLOAT;

  /* Open the output file. */
  if (!(record->sf = sf_open(record->filename, SFM_WRITE, &info))) {
    printf("Not able to open output file %s.\n", record->filename);
    puts(sf_strerror(NULL));
    return NULL;
  };

  record->process = mosaicsound_record_process;
  record->input0 = malloc(framesPerBuffer * sizeof(float));

  return record;
}

void mosaicsound_record_process(mosaicsound_record_t *record) {
  if (record->currentTime >= record->time) {
    record->process = mosaicsound_record_finished;
    sf_close(record->sf);
    printf(">> Rec finished:\n\tFile: %s\n\tTime: %ds\n", record->filename,
           record->time);
    return;
  }

  if (!record->paused) {
    if (record->writeCount >= 44100 * (record->currentTime + 1)) {
      record->currentTime++;
    }
    record->writeCount += record->framesPerBuffer;
    sf_write_float(record->sf, record->input0, record->framesPerBuffer);
  }
}

void mosaicsound_record_finished() { return; }
