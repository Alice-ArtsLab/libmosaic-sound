#include <sndfile.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "include/sndfile.h"

sndfile_t *create_sndfile(char type, char *filename, int framesPerBuffer) {

  sndfile_t *sndfile = malloc(sizeof(sndfile_t));
  sndfile->readCount = 0;
  sndfile->finished = 0;

  sndfile->filename = malloc(strlen(filename) + 1);
  strcpy(sndfile->filename, filename);

    printf("----------------- %s \n", sndfile->filename);

  if (type == 'w') {
    sndfile->process = sndfile_write_process;
  } else {
    sndfile->output = malloc(framesPerBuffer * sizeof(float));
    sndfile->process = sndfile_read_process;
    sndfile->sf = sf_open(sndfile->filename, SFM_READ, &sndfile->info);
    if (!sndfile->sf) {
      printf("Not able to open input file %s.\n", sndfile->filename);
      puts(sf_strerror(NULL));
      return NULL;
    }
  }
  return sndfile;
}

void sndfile_write_process() {}

void sndfile_read_process(sndfile_t *sndfile) {
  if (sndfile->finished) {
    int i = 0;
    for (i = 0; i < sndfile->framesPerBuffer; i++) {
      sndfile->output[i] = 0;
    }
    return;
  }

    sndfile->readCount = sf_read_float(sndfile->sf, sndfile->output,
                                          sndfile->framesPerBuffer)

  if (()) {
  } else {
    sf_close(sndfile->sf);
    sndfile->finished = 1;
  }
}
