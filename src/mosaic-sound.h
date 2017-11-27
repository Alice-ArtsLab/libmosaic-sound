
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


static int mosaicsound_callback();
static void mosaicsound_finished(void *data);
static void mosaicsound_inicialize();
static void mosaicsound_termite(void *stream);
