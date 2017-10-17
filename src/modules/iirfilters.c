#include <math.h>
#include <stdlib.h>
#include "include/iirfilters.h"

iir_t *create_iir(int type, int order, int framesPerBuffer) {
  iir_t *filter = malloc(sizeof(iir_t));

  filter->type = type;
  filter->order = order;
  filter->framesPerBuffer = framesPerBuffer;
  filter->output = malloc(framesPerBuffer * sizeof(float));

  switch (type) {
    case 0:
      filter->process = allpass_process;
      break;
    case 1:
      filter->process = lowpass_process;
      break;
    case 2:
      filter->process = highpass_process;
      break;
    case 3:
      filter->process = bandpass_process;
      break;
    case 4:
      filter->process = bandreject_process;
      break;
  }

  return filter;
}

void allpass_process(iir_t *filter) {
  if (filter->order == 1) { /* First-order allpass */
    float c = (tan(M_PI * (filter->cutOff) / (filter->sampleRate) - 1)) /
              (tan(M_PI * (filter->cutOff) / (filter->sampleRate) +
                   1)); /* coefficient */

    for (int i = 0; i < filter->framesPerBuffer; i++) {
      filter->output[i] =
          (pow(filter->input[i], -1) + c) / (1 + c * pow(filter->input[i], -1));
    }

  } else { /* Second-order allpass */
    float c = (tan(M_PI * (filter->slope) / (filter->sampleRate) - 1)) /
              (tan(M_PI * (filter->slope) / (filter->sampleRate) +
                   1)); /* Bandwidth */
    float d = -cos(2 * M_PI * (filter->cutOff) /
                   (filter->sampleRate)); /* Adjust the cut-off frequency */

    for (int i = 0; i < filter->framesPerBuffer; i++) {
      filter->output[i] = (-c + (d * (1 - c) * pow(filter->input[i], -1)) +
                           pow(filter->input[i], -2)) /
                          (1 + (d * (1 - c) * pow(filter->input[i], -1)) -
                           (c * pow(filter->input[i], -2)));
    }
  }
}

void lowpass_process(iir_t *filter) {}

void highpass_process(iir_t *filter) {}

void bandpass_process(iir_t *filter) {}

void bandreject_process(iir_t *filter) {}
