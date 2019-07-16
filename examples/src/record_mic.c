#include <mosaic-sound.h>
#include <portaudio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

  mic->process(mic, in);
  rec->input0 = mic->output0;
  rec->process(rec);
  speaker->input0 = mic->output0;
  speaker->process(speaker, out);

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
      mscsound_create_record("./record_mic.wav", FRAMES_PER_BUFFER, 10, 44100);
  speaker = mscsound_create_speaker(FRAMES_PER_BUFFER);

  void *stream = mscsound_inicialize(SAMPLE_RATE, FRAMES_PER_BUFFER);

  printf("Recording until the Enter key is pressed.\n");
  getchar();

  mscsound_terminate(stream);

  return 0;
}
