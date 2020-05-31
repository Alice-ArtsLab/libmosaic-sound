#include <gtk/gtk.h>
#include <mosaic-sound.h>
#include <portaudio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_SECONDS 12
#define SAMPLE_RATE 44100
#define FRAMES_PER_BUFFER 256

mscsound_osc_t *osc;
mscsound_volume_t *volume;
mscsound_audiofloatmath_t *mul;
mscsound_waveform_t *waveform;
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
  (void)in;
  (void)out;

  osc->process(&osc);
  mul->process(&mul);
  waveform->process(&waveform);
  speaker->process(&speaker, &out);

  return paContinue;
}

/*
 * This routine is called by mscsound when mscsound_callback is done.
 */

void destroy(void) { gtk_main_quit(); }

static void mscsound_finished(void *data) { printf("Stream Completed!\n"); }

/*******************************************************************/
int main(int argc, char *argv[]) {
  mscsound_gui_t *gui = mscsound_create_gui("Waveform", 800, 600);

  /* Sine 440.0 Hz */
  osc = mscsound_create_osc("sine", FRAMES_PER_BUFFER, 2048);
  osc->sampleRate = SAMPLE_RATE;
  osc->input0 = NULL;
  float osc1FreqValue = 440.0;
  osc->input1 = &osc1FreqValue;

  waveform = mscsound_create_waveform(200, 200, FRAMES_PER_BUFFER);
  gui->add(&gui, &(waveform->widget));
  speaker = mscsound_create_speaker(FRAMES_PER_BUFFER);

  volume = mscsound_create_volume("Volume: ");
  gui->add(&gui, &(volume->widget));

  mul = mscsound_create_audiofloatmath(FRAMES_PER_BUFFER,
                                       mscsound_mul_freq_float);

  mul->input0 = osc->output0;
  mul->input1 = volume->output0;

  waveform->input0 = mul->output0;
  speaker->input0 = mul->output0;

  void *stream = mscsound_initialize(SAMPLE_RATE, FRAMES_PER_BUFFER);

  gui->start(&gui);

  mscsound_terminate(stream);

  return 0;
}
