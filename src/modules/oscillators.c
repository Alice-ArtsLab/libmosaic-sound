#include <getopt.h>
#include <math.h>
#include <portaudio.h>
#include <stdio.h>

#define NUM_SECONDS (5)
#define SAMPLE_RATE (48000)
#define FRAMES_PER_BUFFER (64)
float FREQ;

/* This routine will be called by the PortAudio engine when audio is needed.
** It may called at interrupt level on some machines so don't do anything
** that could mess up the system like calling malloc() or free().
*/

float *create_sine_table(float *table) {
  table = malloc(TABLE_SIZE * sizeof(float));
  int i;
  for (i = 0; i < TABLE_SIZE; i++) {
    table[i] = sin(2.0 * M_PI * i / TABLE_SIZE);
  }
  return table;
}

float *create_square_table(float *table) {
  table = malloc(TABLE_SIZE * sizeof(float));
  int i;
  for (i = 0; i < TABLE_SIZE; i++) {
    table[i] = sin(2.0 * M_PI * i / TABLE_SIZE);
    if (table[i] >= 0) {
      table[i] = 1;
    } else {
      table[i] = -1;
    }
  }
  return table;
}

float *create_triangle_table(float *table) {
  table = malloc(TABLE_SIZE * sizeof(float));
  int i;
  for (i = 0; i < TABLE_SIZE; i++) {
    table[i] = (2 / M_PI) * asin(sin((2 * M_PI * i) / TABLE_SIZE));
  }
  return table;
}

float *create_sawtooth_table(float *table) {
  table = malloc(TABLE_SIZE * sizeof(float));
  int i;
  for (i = 0; i < TABLE_SIZE; i++) {
    table[i] = (2 / M_PI) * atan(tan((2 * M_PI * i) / (2 * TABLE_SIZE)));
  }
  return table;
}

/*
Standar function to get interpolated values in a sine table
*/
float get_interpolated_freq(wave_table *data, float frequency, float sr) {
  int my_floor = floor(data->index);
  float y = data->index - my_floor;

  // Definicao de indexs circulares
  int index1 = (my_floor - 1 >= 0) ? my_floor - 1 : TABLE_SIZE + (my_floor - 1);
  int index2 = my_floor;
  int index3 =
      (my_floor + 1 < TABLE_SIZE) ? my_floor + 1 : my_floor + 1 - TABLE_SIZE;
  int index4 =
      (my_floor + 2 < TABLE_SIZE) ? my_floor + 2 : my_floor + 2 - TABLE_SIZE;
  //	float v_interpolado = table[my_floor]; // SEM INTERPOLACAO
  //	float v_interpolado = ((1.0 - (y)) * table[index2] + (y) *
  // table[index3]); // INTERPOLACAO LINEAR

  float v_interpolado =
      -((y) * (y - 1) * (y - 2) * data->table[index1]) /
          6  // INTERPOLACAO CUBICA
      + ((y + 1) * (y - 1) * (y - 2) * data->table[index2]) / 2 -
      ((y + 1) * (y) * (y - 2) * data->table[index3]) / 2 +
      ((y + 1) * (y) * (y - 1) * data->table[index4]) / 6;

  // proximo index a ser lido para esta frequencia
  data->index += TABLE_SIZE * frequency /
                 sr;  // Tamanho da tabela * frequencia / Sample rate
  if (data->index >= TABLE_SIZE)  // Truncamento pelo tamanho da tabela seno
    data->index -= TABLE_SIZE;

  return v_interpolado;
}

static int oscillatorCallback(const void *inputBuffer, void *outputBuffer,
                              unsigned long framesPerBuffer,
                              const PaStreamCallbackTimeInfo *timeInfo,
                              PaStreamCallbackFlags statusFlags,
                              void *userData) {
  wave_table *data = (wave_table *)userData;
  float *out = (float *)outputBuffer;
  unsigned long i;

  (void)timeInfo; /* Prevent unused variable warnings. */
  (void)statusFlags;
  (void)inputBuffer;

  for (i = 0; i < framesPerBuffer; i++) {
    out[i] = get_interpolated_freq(data, FREQ, SAMPLE_RATE);
  }

  return paContinue;
}

/*
 * This routine is called by portaudio when playback is done.
 */
static void StreamFinished(void *userData) {
  wave_table *data = (wave_table *)userData;
  printf("Stream Completed!\n");
}

/*******************************************************************/
int main(int argc, char *argv[]) {
  PaStreamParameters outputParameters;
  PaStream *stream;
  PaError err;
  int i;

  wave_table data;
  data.index = 0;

  char optc = 0;

  struct option op[] = {{"whitenoise", no_argument, NULL, 'w'},
                        {"sine", required_argument, NULL, 's'},
                        {"sawtooth", required_argument, NULL, 'a'},
                        {"square", required_argument, NULL, 'q'},
                        {"triangle", required_argument, NULL, 't'},
                        {"help", no_argument, NULL, 'h'},
                        {0, 0, 0, 0}};

  FREQ = 440.0;
  data.table = create_sine_table(data.table);

  err = Pa_Initialize();
  if (err != paNoError) goto error;

  outputParameters.device =
      Pa_GetDefaultOutputDevice(); /* default output device */
  if (outputParameters.device == paNoDevice) {
    fprintf(stderr, "Error: No default output device.\n");
    goto error;
  }
  outputParameters.channelCount = 1;         /* stereo output */
  outputParameters.sampleFormat = paFloat32; /* 32 bit floating point output */
  outputParameters.suggestedLatency =
      Pa_GetDeviceInfo(outputParameters.device)->defaultLowOutputLatency;
  outputParameters.hostApiSpecificStreamInfo = NULL;
  err = Pa_OpenStream(&stream, NULL, /* no input */
                      &outputParameters, SAMPLE_RATE, FRAMES_PER_BUFFER,
                      paClipOff, /* we won't output out of range samples so
                                    don't bother clipping them */
                      oscillatorCallback, &data);
  if (err != paNoError) goto error;

  err = Pa_SetStreamFinishedCallback(stream, &StreamFinished);
  if (err != paNoError) goto error;

  err = Pa_StartStream(stream);
  if (err != paNoError) goto error;

  printf("Play for %d seconds.\n", NUM_SECONDS);
  Pa_Sleep(NUM_SECONDS * 1000);

  err = Pa_StopStream(stream);
  if (err != paNoError) goto error;

  err = Pa_CloseStream(stream);
  if (err != paNoError) goto error;

  Pa_Terminate();
  printf("Test finished.\n");

  return err;
error:
  Pa_Terminate();
  fprintf(stderr, "An error occured while using the portaudio stream\n");
  fprintf(stderr, "Error number: %d\n", err);
  fprintf(stderr, "Error message: %s\n", Pa_GetErrorText(err));
  return err;
}
