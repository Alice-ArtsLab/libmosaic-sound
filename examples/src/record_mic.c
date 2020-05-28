#include <mosaic-sound.h>
#include <portaudio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define NUM_SECONDS 12
#define SAMPLE_RATE 44100
#define FRAMES_PER_BUFFER 256

mscsound_mic_t *mic;
mscsound_record_t *rec;
mscsound_speaker_t *speaker;

static int mscsound_callback(const void *inputBuffer, void *outputBuffer,
                             unsigned long framesPerBuffer,
                             const PaStreamCallbackTimeInfo *timeInfo,
                             PaStreamCallbackFlags statusFlags,
                             void *userData) {
  float *in = (float *)inputBuffer;
  float *out = (float *)outputBuffer;

  (void)timeInfo; /* Prevent unused variable warnings. */
  (void)statusFlags;
  (void)userData;

  mic->process(&mic, &in);
  rec->process(&rec);
  speaker->process(&speaker, &out);

  return paContinue;
}

/*
 * This routine is called by mscsound when mscsound_callback is done.
 */
static void mscsound_finished(void *data) { printf("Stream Completed!\n"); }

/*******************************************************************/
int main(int argc, char *argv[]) {
  mic = mscsound_create_mic(FRAMES_PER_BUFFER);
  rec =
      mscsound_create_record("./record_mic.wav", FRAMES_PER_BUFFER, 44100);
  speaker = mscsound_create_speaker(FRAMES_PER_BUFFER);

  rec->input0 = mic->output0;
  speaker->input0 = mic->output0;

  void *stream = mscsound_initialize(SAMPLE_RATE, FRAMES_PER_BUFFER);


  printf("Recording... Wait 10 seconds!\n");
  sleep(10);
  strcpy(*(rec->stop), "yes");
  
  mscsound_terminate(stream);

  return 0;
}
