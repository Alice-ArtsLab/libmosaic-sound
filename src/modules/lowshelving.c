#include <math.h>
#include <stdlib.h>
#include "include/lowshelving.h"

mosaicsound_lowshelving_t *mosaicsound_create_lowshelving(int framesPerBuffer) {
  mosaicsound_lowshelving_t *filter = malloc(sizeof(mosaicsound_lowshelving_t));

  filter->framesPerBuffer = framesPerBuffer;
  filter->output = malloc(framesPerBuffer * sizeof(float));
  filter->xn1 = 0;
  filter->xn2 = 0;
  filter->yn1 = 0;
  filter->yn2 = 0;
  filter->process = mosaicsound_lowshelving_process;

  return filter;
}

void mosaicsound_lowshelving_process(mosaicsound_lowshelving_t *filter) {
  float K = (float)tan(M_PI * filter->cutOff / filter->sampleRate);
  float V0 = pow(10, (filter->gain / 20));
  float b0 = 1, b1 = 0, b2 = 0, a1 = 0, a2 = 0;

  if (filter->gain >= 1) {  // boost
    b0 = (1 + sqrt(2 * V0) * K + V0 * K * K) / (1 + sqrt(2) * K + K * K);
    b1 = (2 * (V0 * K * K - 1)) / (1 + sqrt(2) * K + K * K);
    b2 = (1 - sqrt(2 * V0) * K + V0 * K * K) / (1 + sqrt(2) * K + K * K);
    a1 = (2 * (K * K - 1)) / (1 + sqrt(2) * K + K * K);
    a2 = (1 - sqrt(2) * K + K * K) / (1 + sqrt(2) * K + K * K);
  }
  if (filter->gain < 0) {  // cut
    b0 = (V0 * (1 + sqrt(2) * K + K * K)) / (V0 + sqrt(2 * V0) * K + K * K);
    b1 = (2 * V0 * (K * K - 1)) / (V0 + sqrt(2 * V0) * K + K * K);
    b2 = (V0 * (1 - sqrt(2) * K + K * K)) / (V0 + sqrt(2 * V0) * K + K * K);
    a1 = (2 * (K * K - V0)) / (V0 + sqrt(2 * V0) * K + K * K);
    a2 = (V0 - sqrt(2 * V0) * K + K * K) / (V0 + sqrt(2 * V0) * K + K * K);
  }

  int i = 0;
  for (i = 0; i < filter->framesPerBuffer; i++) {
    filter->output[i] = b0 * filter->input[i] + b1 * filter->xn1 +
                        b2 * filter->xn2 - a1 * filter->yn1 - a2 * filter->yn2;
    filter->xn2 = filter->xn1;
    filter->yn2 = filter->yn1;
    filter->xn1 = filter->input[i];
    filter->yn1 = filter->output[i];
  }
}
