#include "include/channelshootersplitter.h"
#include <stdlib.h>
#include <string.h>

mscsound_channelshootersplitter_t *
mscsound_create_channelshootersplitter(int framesPerBuffer) {
  mscsound_channelshootersplitter_t *css =
      malloc(sizeof(mscsound_channelshootersplitter_t));

  css->framesPerBuffer = framesPerBuffer;
  css->output0 = malloc(sizeof(float) * framesPerBuffer);
  css->process = mscsound_channelshootersplitter_process;

  return css;
}

void mscsound_channelshootersplitter_process(
    mscsound_channelshootersplitter_t *css) {

  int i;
  for (i = 0; i < css->framesPerBuffer; i++)
    css->output0[i] = css->input0[i];
}
