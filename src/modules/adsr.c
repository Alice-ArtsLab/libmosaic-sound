#include "include/adsr.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

void restart_adsr (mscsound_adsr_t **adsr) {
  (*adsr)->play = 0;
  (*adsr)->initialSample = 0;
  (*adsr)->currentSample = 0;
  (*adsr)->currentAmplitude = 0;
  (*adsr)->currentFrame = 0;
}

mscsound_adsr_t *mscsound_create_adsr(int sampleRate, int framesPerBuffer) {
  mscsound_adsr_t *adsr = malloc(sizeof(mscsound_adsr_t));

  adsr->output0 = calloc(1, sizeof(float*));
  adsr->framesPerBuffer = framesPerBuffer;
  adsr->sampleRate = sampleRate;
  adsr->attack = 0.0;
  adsr->decay = 0.0;
  adsr->sustain = 0.0;
  adsr->release = 0.0;
  adsr->gain = 0.8;
  adsr->play = 0;
  adsr->initialSample = 0;
  adsr->currentSample = 0;
  adsr->finalSample = 0;
  adsr->currentAmplitude = 0;
  adsr->currentFrame = 0;

  adsr->process = mscsound_process_silence;
  return adsr;
}

void mscsound_process_silence(mscsound_adsr_t **adsr){
  *((*adsr)->output0) = *((*adsr)->input0);

  if (! (*adsr)->play) {
    for (int i = 0; i < (*adsr)->framesPerBuffer; i++)
      (*((*adsr)->output0))[i] = 0.0;
  } else {
    (*adsr)->process = mscsound_process_attack;
    (*adsr)->finalSample = (((*adsr)->sampleRate * (*adsr)->attack) / 1000) - 1;
    (*adsr)->process(adsr);
  }
}

void mscsound_process_attack(mscsound_adsr_t **adsr) {
  *((*adsr)->output0) = *((*adsr)->input0);

  if ((*adsr)->play)
    restart_adsr(adsr);

  float amplitudeStep = 1 / (float)(((*adsr)->finalSample) - \
                                                  (*adsr)->initialSample);
  int remainingSamples = (*adsr)->finalSample + 1 - (*adsr)->currentSample;
  if (remainingSamples > (*adsr)->framesPerBuffer) {
    for (int i = (*adsr)->currentFrame; i < (*adsr)->framesPerBuffer; i++) {
      (*((*adsr)->output0))[i] *= (*adsr)->currentAmplitude;
      ((*adsr)->currentFrame)++;
      ((*adsr)->currentSample)++;
      ((*adsr)->currentAmplitude) += amplitudeStep;

    }

  } else {
    for (int i = (*adsr)->currentFrame; i < remainingSamples; i++) {
      (*((*adsr)->output0))[i] *= (*adsr)->currentAmplitude;
      ((*adsr)->currentFrame)++;
      ((*adsr)->currentSample)++;
      ((*adsr)->currentAmplitude) += amplitudeStep;
    }

    (*adsr)->process = mscsound_process_decay;
    (*adsr)->initialSample = (*adsr)->currentSample;
    (*adsr)->finalSample += (((*adsr)->sampleRate * (*adsr)->decay) / 1000) -1;
    if (remainingSamples != (*adsr)->framesPerBuffer)
      (*adsr)->process(adsr);
  }
  ((*adsr)->currentFrame) = 0;
}


void mscsound_process_decay(mscsound_adsr_t **adsr) {
  *((*adsr)->output0) = *((*adsr)->input0);

  if ((*adsr)->play) {
    restart_adsr(adsr);
    (*adsr)->process = mscsound_process_attack;
    (*adsr)->process(adsr);
    return;
  }

  float amplitudeStep = (1 - (*adsr)->gain) / \
            (float)((*adsr)->finalSample - (float)((*adsr)->initialSample));

  int remainingSamples = (*adsr)->finalSample + 1 - (*adsr)->currentSample;

  if (remainingSamples > (*adsr)->framesPerBuffer) {
    for (int i = (*adsr)->currentFrame; i < (*adsr)->framesPerBuffer; i++) {
      ((*adsr)->currentAmplitude) -= amplitudeStep;
      (*((*adsr)->output0))[i] *= (*adsr)->currentAmplitude;
      ((*adsr)->currentFrame)++;
      ((*adsr)->currentSample)++;
    }

  } else {
    for (int i = (*adsr)->currentFrame; i < remainingSamples; i++) {
      ((*adsr)->currentAmplitude) -= amplitudeStep;
      (*((*adsr)->output0))[i] *= (*adsr)->currentAmplitude;
      ((*adsr)->currentFrame)++;
      ((*adsr)->currentSample)++;
    }

    (*adsr)->process = mscsound_process_sustain;
    (*adsr)->initialSample = (*adsr)->currentSample;
    (*adsr)->finalSample += (((*adsr)->sampleRate * (*adsr)->sustain) / 1000)-1;
    if (remainingSamples != (*adsr)->framesPerBuffer)
      (*adsr)->process(adsr);
  }
  ((*adsr)->currentFrame) = 0;
}

void mscsound_process_sustain(mscsound_adsr_t **adsr) {
  *((*adsr)->output0) = *((*adsr)->input0);

  if ((*adsr)->play) {
    restart_adsr(adsr);
    (*adsr)->process = mscsound_process_attack;
    (*adsr)->process(adsr);
    return;
  }

  int remainingSamples = (*adsr)->finalSample + 1 - (*adsr)->currentSample;

  if (remainingSamples > (*adsr)->framesPerBuffer) {
    for (int i = (*adsr)->currentFrame; i < (*adsr)->framesPerBuffer; i++) {
      (*((*adsr)->output0))[i] *= (*adsr)->currentAmplitude;
      ((*adsr)->currentFrame)++;
      ((*adsr)->currentSample)++;
    }

  } else {
    for (int i = (*adsr)->currentFrame; i < remainingSamples; i++) {
      (*((*adsr)->output0))[i] *= (*adsr)->currentAmplitude;
      ((*adsr)->currentFrame)++;
      ((*adsr)->currentSample)++;
    }

    (*adsr)->process = mscsound_process_release;
    (*adsr)->initialSample = (*adsr)->currentSample;
    (*adsr)->finalSample += (((*adsr)->sampleRate * (*adsr)->release) / 1000)-1;
    if (remainingSamples != (*adsr)->framesPerBuffer)
      (*adsr)->process(adsr);
  }
  ((*adsr)->currentFrame) = 0;
}

void mscsound_process_release(mscsound_adsr_t **adsr) {
  *((*adsr)->output0) = *((*adsr)->input0);

  if ((*adsr)->play) {
    restart_adsr(adsr);
    (*adsr)->process = mscsound_process_attack;
    (*adsr)->process(adsr);
    return;
  }

  float amplitudeStep = (*adsr)->currentAmplitude / \
            (float)((*adsr)->finalSample - (*adsr)->currentSample);

  int remainingSamples = (*adsr)->finalSample + 1 - (*adsr)->currentSample;

  if (remainingSamples > (*adsr)->framesPerBuffer) {
    for (int i = (*adsr)->currentFrame; i < (*adsr)->framesPerBuffer; i++) {
      ((*adsr)->currentAmplitude) -= amplitudeStep;
      (*((*adsr)->output0))[i] *= (*adsr)->currentAmplitude;
      ((*adsr)->currentFrame)++;
      ((*adsr)->currentSample)++;
    }

  } else {

    for (int i = (*adsr)->currentFrame; i < remainingSamples; i++) {
      ((*adsr)->currentAmplitude) -= amplitudeStep;
      (*((*adsr)->output0))[i] *= (*adsr)->currentAmplitude;
      ((*adsr)->currentFrame)++;
      ((*adsr)->currentSample)++;
    }

    if (remainingSamples != (*adsr)->framesPerBuffer) {
      for (int i = (*adsr)->currentFrame; i < (*adsr)->framesPerBuffer; i++)
        (*((*adsr)->output0))[i] *= 0.0;
        ((*adsr)->currentFrame)++;
        ((*adsr)->currentSample)++;
    }

    restart_adsr(adsr);
    (*adsr)->process = mscsound_process_silence;
  }
  ((*adsr)->currentFrame) = 0;
}
