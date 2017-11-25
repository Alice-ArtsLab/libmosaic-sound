
#include "modules/include/audiomath.h"
#include "modules/include/biquad.h"
#include "modules/include/devices.h"
#include "modules/include/highshelving.h"
#include "modules/include/lowshelving.h"
#include "modules/include/mic.h"
#include "modules/include/oscillators.h"
#include "modules/include/parametricequalizer.h"
#include "modules/include/playback.h"
#include "modules/include/record.h"
#include "modules/include/whitenoise.h"

static int mosaicsound_callback(const void *inputBuffer, void *outputBuffer,
                                unsigned long framesPerBuffer,
                                const PaStreamCallbackTimeInfo *timeInfo,
                                PaStreamCallbackFlags statusFlags,
                                void *userData);

/*
 * This routine is called by mosaic-sound when portaudio playback is done.
 */

static void mosaicsound_finished(void *data);

/*
 * This routine is called by portaudio when playback is done.
 */
static void StreamFinished(void *data) {mosaicsound_finished(data);}

int mosaicsound_initialize(int framesPerBuffer, int sampleRate) {
  PaStreamParameters inputParameters, outputParameters;
  PaStream *stream;
  PaError err;

  err = Pa_Initialize();
  if (err != paNoError) goto error;
  /*-------------------------------------------------------------------------*/

  /*inputParameters*/
  inputParameters.device =
      Pa_GetDefaultInputDevice(); /* default input device */
  if (inputParameters.device == paNoDevice) {
    fprintf(stderr, "Error: No default input device.\n");
    goto error;
  }
  inputParameters.channelCount = 1; /* mono input */
  inputParameters.sampleFormat = paFloat32;
  inputParameters.suggestedLatency =
      Pa_GetDeviceInfo(inputParameters.device)->defaultLowInputLatency;
  inputParameters.hostApiSpecificStreamInfo = NULL;

  /*-------------------------------------------------------------------------*/
  /*outputParameters*/
  outputParameters.device =
      Pa_GetDefaultOutputDevice(); /* default output device */
  if (outputParameters.device == paNoDevice) {
    fprintf(stderr, "Error: No default output device.\n");
    goto error;
  }
  outputParameters.channelCount = 1;         /* mono output */
  outputParameters.sampleFormat = paFloat32; /* 32 bit floating point output */
  outputParameters.suggestedLatency =
      Pa_GetDeviceInfo(outputParameters.device)->defaultLowOutputLatency;
  outputParameters.hostApiSpecificStreamInfo = NULL;
  err = Pa_OpenStream(&stream, &inputParameters, &outputParameters, sampleRate,
                      framesPerBuffer,
                      paClipOff, /* we won't output out of range samples so
                                    don't bother clipping them */
                      mosaicsound_callback, NULL);
  if (err != paNoError) goto error;

  err = Pa_SetStreamFinishedCallback(stream, &StreamFinished);
  if (err != paNoError) goto error;

  err = Pa_StartStream(stream);
  if (err != paNoError) goto error;

  return err;

error:
  Pa_Terminate();
  fprintf(stderr, "An error occured while using the portaudio stream\n");
  fprintf(stderr, "Error number: %d\n", err);
  fprintf(stderr, "Error message: %s\n", Pa_GetErrorText(err));
  return err;
}

void mosaicsound_terminate() { Pa_Terminate(); }
