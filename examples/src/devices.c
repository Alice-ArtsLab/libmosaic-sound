
#include <stdio.h>
#include <stdlib.h>
#include "../../src/modules/include/audiomath.h"
#include "../../src/modules/include/biquad.h"
#include "../../src/modules/include/devices.h"
#include "../../src/modules/include/highshelving.h"
#include "../../src/modules/include/lowshelving.h"
#include "../../src/modules/include/mic.h"
#include "../../src/modules/include/oscillators.h"
#include "../../src/modules/include/parametricequalizer.h"
#include "../../src/modules/include/playback.h"
#include "../../src/modules/include/record.h"
#include "../../src/modules/include/whitenoise.h"

#define NUM_SECONDS 12
#define SAMPLE_RATE 44100
#define FRAMES_PER_BUFFER 256
#define CHANNELCOUNT 1 /* mono output */

/*******************************************************************/
int main(int argc, char *argv[]) {
  device_list_t *devices = create_devices();
  devices->process(devices);
  devices->show(devices);
}
