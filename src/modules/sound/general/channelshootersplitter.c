#include "include/channelshootersplitter.h"
#include <stdlib.h>
#include <string.h>

mscsound_channelshootersplitter_t *
mscsound_create_channelshootersplitter(int framesPerBuffer) {
  mscsound_channelshootersplitter_t *css =
      malloc(sizeof(mscsound_channelshootersplitter_t));

  css->framesPerBuffer = framesPerBuffer;
  css->output0 = calloc(1, sizeof(float*));
  css->output0[0] = calloc(framesPerBuffer, sizeof(float));
  css->process = mscsound_channelshootersplitter_process;

  return css;
}

void mscsound_channelshootersplitter_process(
    mscsound_channelshootersplitter_t **css) {

  int i;
  for (i = 0; i < (*css)->framesPerBuffer; i++)
    (*((*css)->output0))[i] = (*((*css)->input0))[i];
}
