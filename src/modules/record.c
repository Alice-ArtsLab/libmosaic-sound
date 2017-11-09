#include <sndfile.h>
#include <sndfile.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/record.h"

sndfile_t *create_record(char *filename, int framesPerBuffer) {
  record_t *record = malloc(sizeof(record_t));

  record->filename = malloc(strlen(filename) + 1);
  strcpcy(record->filename, filename);

  record->process = record_process;

  record->input = malloc(framesPerBuffer * sizeof(float));
  record->process = record_process;

  return record;
}

void record_process(record_t *record) {}
