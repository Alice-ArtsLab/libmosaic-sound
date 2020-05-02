#include "include/record.h"
#include <sndfile.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

mscsound_record_t *mscsound_create_record(char *filename,
                                                int framesPerBuffer, int sr) {
  mscsound_record_t *record = malloc(sizeof(mscsound_record_t));

  record->writeCount = 0;
  record->currentTime = 0;

  record->paused = calloc(1, sizeof(char*));
  record->paused[0] = calloc(4, sizeof(char)); // strlen("yes") + 1
  strcpy(*(record->paused), "no");

  record->stop = calloc(1, sizeof(char*));
  record->stop[0] = calloc(4, sizeof(char)); // strlen("yes") + 1
  strcpy(*(record->stop), "no");

  record->sampleRate = sr;
  record->framesPerBuffer = framesPerBuffer;
  record->filename = calloc(1, sizeof(char*));
  record->filename[0] = calloc(strlen(filename) + 1, sizeof(char));
  strcpy(*(record->filename), filename);

  SF_INFO info;
  record->sf = (SNDFILE *)record->sf;
  info.samplerate = record->sampleRate;
  info.channels = 1;
  info.format = SF_FORMAT_WAV | SF_FORMAT_FLOAT;

  /* Open the output file. */
  if (!(record->sf = sf_open(*(record->filename), SFM_WRITE, &info))) {
    printf("Not able to open output file %s.\n", *(record->filename));
    puts(sf_strerror(NULL));
    return NULL;
  };

  record->process = mscsound_record_process;
  record->input0 = calloc(1, sizeof(float*));
  record->input0[0] = calloc(framesPerBuffer, sizeof(float));

  return record;
}

void mscsound_record_process(mscsound_record_t **record) {
  if (! strcmp(*((*record)->stop), "yes")) {
    (*record)->process = mscsound_record_finished;
    sf_close((*record)->sf);
    printf(">> Rec finished:\n\tFile: %s\n\tTime: %ds\n", *((*record)->filename),
           (*record)->currentTime);
    return;
  }

  if (! strcmp(*((*record)->paused), "no")) { // record->paused = "no"
    if ((*record)->writeCount >= 44100 * ((*record)->currentTime + 1)) {
      (*record)->currentTime++;
    }
    (*record)->writeCount += (*record)->framesPerBuffer;
    sf_write_float((*record)->sf, *((*record)->input0), (*record)->framesPerBuffer);
  }
}

void mscsound_record_finished() { return; }
