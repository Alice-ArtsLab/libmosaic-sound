#include <sndfile.h>
#include <stdio.h>
#include <stdlib.h>
#include "include/sndfile.h"

sndfile_t *create_sndfile(char type, char *filename, int framesPerBuffer) {
  sndfile_t *sndfile = malloc(sizeof(sndfile_t));
  sndfile->readCount = 0;
  sndfile->finished = 0;
  sndfile->filename = filename;
  sndfile->output = malloc(framesPerBuffer * sizeof(float));

  if (type == 'w') {
    sndfile->process = sndfile_write_process;
  } else {
    sndfile->process = sndfile_read_process;

    sndfile->infile = (SNDFILE *)sndfile->infile;
    sndfile->sfinfo = (SF_INFO *)sndfile->sfinfo;

    sndfile->infile = sf_open(sndfile->filename, SFM_READ, sndfile->sfinfo);
    if (!sndfile->infile) {
      printf("Not able to open input file %s.\n", sndfile->filename);
      /* Print the error message from libsndfile. */
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
  }
  if ((sndfile->readCount = sf_read_float(sndfile->infile, sndfile->output,
                                          sndfile->framesPerBuffer))) {
  } else {
    sf_close(sndfile->infile);
    sndfile->finished = 1;
  }
}
