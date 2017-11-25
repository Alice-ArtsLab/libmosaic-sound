#include <stdio.h>
#include <stdlib.h>
#include "mosaic-sound.h"

static int speakerCallback(const void *inputBuffer, void *outputBuffer,
                           unsigned long framesPerBuffer,
                           const PaStreamCallbackTimeInfo *timeInfo,
                           PaStreamCallbackFlags statusFlags, void *userData) {}

/*
 * This routine is called by portaudio when playback is done.
 */
static void StreamFinished(void *data) {}

/*******************************************************************/
int main(int argc, char *argv[]) { return 0; }
