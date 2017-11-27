#ifndef MOSAIC_SOUND_H
#define MOSAIC_SOUND_H

    #include "/usr/include/mosaic/mosaic-sound/include/audiomath.h"
    #include "/usr/include/mosaic/mosaic-sound/include/biquad.h"
    #include "/usr/include/mosaic/mosaic-sound/include/devices.h"
    #include "/usr/include/mosaic/mosaic-sound/include/highshelving.h"
    #include "/usr/include/mosaic/mosaic-sound/include/lowshelving.h"
    #include "/usr/include/mosaic/mosaic-sound/include/mic.h"
    #include "/usr/include/mosaic/mosaic-sound/include/oscillators.h"
    #include "/usr/include/mosaic/mosaic-sound/include/parametricequalizer.h"
    #include "/usr/include/mosaic/mosaic-sound/include/playback.h"
    #include "/usr/include/mosaic/mosaic-sound/include/record.h"
    #include "/usr/include/mosaic/mosaic-sound/include/whitenoise.h"

    static int mosaicsound_callback();
    static void mosaicsound_finished(void *data);
    /*
    * This routine is called by portaudio when playbak is done.
    */
    static void StreamFinished(void *data) { mosaicsound_finished(data); }

    static void * mosaicsound_inicialize(int sampleRate, int framesPerBuffer) {
      PaStreamParameters inputParameters, outputParameters;
      PaStream *stream;
      PaError err;

      err = Pa_Initialize();
      if (err != paNoError) goto error;

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
      outputParameters.channelCount = 1; /* mono output */
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

      return (void *)stream;

    error:
      Pa_Terminate();
      fprintf(stderr, "An error occured while using the portaudio stream\n");
      fprintf(stderr, "Error number: %d\n", err);
      fprintf(stderr, "Error message: %s\n", Pa_GetErrorText(err));
      return NULL;
    }

    static void mosaicsound_terminate(void *stream) {
      PaError err;
      stream = (PaStream *)stream;
      err = Pa_StopStream(stream);
      if (err != paNoError) goto error;

      err = Pa_CloseStream(stream);
      if (err != paNoError) goto error;

      Pa_Terminate();

      return;
    error:
      Pa_Terminate();
      fprintf(stderr, "An error occured while using the portaudio stream\n");
      fprintf(stderr, "Error number: %d\n", err);
      fprintf(stderr, "Error message: %s\n", Pa_GetErrorText(err));

    }


#endif /* mosaic-sound.h */
