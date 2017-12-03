#include <math.h>
#include <stdlib.h>
#include "include/oscillators.h"

mosaicsound_osc_t *mosaicsound_create_osc(int type, int framesPerBuffer,
                                          float tableSize) {
  mosaicsound_osc_t *osc = malloc(sizeof(mosaicsound_osc_t));
  osc->type = type;
  osc->framesPerBuffer = framesPerBuffer;
  osc->tableSize = tableSize;
  osc->index = 0;
  osc->output = malloc(framesPerBuffer * sizeof(float));
  osc->process = mosaicsound_osc_process;

  switch (type) {
    case 0:
      osc->table = mosaicsound_create_sine_table(tableSize);
      break;

    case 1:
      osc->table = mosaicsound_create_square_table(tableSize);
      break;
    case 2:
      osc->table = mosaicsound_create_triangle_table(tableSize);

      break;
    case 3:
      osc->table = mosaicsound_create_sawtooth_table(tableSize);
      break;
  }

  return osc;
}
void mosaicsound_osc_process(mosaicsound_osc_t *osc) {
  for (int i = 0; i < osc->framesPerBuffer; i++) {
    osc->output[i] = mosaicsound_get_interpolated_freq(osc);
  }
}

float *mosaicsound_create_sine_table(int tableSize) {
  float *table = malloc(tableSize * sizeof(float));
  int i;
  for (i = 0; i < tableSize; i++) {
    table[i] = sin(2.0 * M_PI * i / tableSize);
  }
  return table;
}

float *mosaicsound_create_square_table(int tableSize) {
  float *table = malloc(tableSize * sizeof(float));
  int i;
  for (i = 0; i < tableSize; i++) {
    table[i] = sin(2.0 * M_PI * i / tableSize);
    if (table[i] >= 0)
      table[i] = 1;
    else
      table[i] = -1;
  }
  return table;
}

float *mosaicsound_create_triangle_table(int tableSize) {
  float *table = malloc(tableSize * sizeof(float));
  int i;
  for (i = 0; i < tableSize; i++) {
    table[i] = (2 / M_PI) * asin(sin((2 * M_PI * i) / tableSize));
  }
  return table;
}

float *mosaicsound_create_sawtooth_table(int tableSize) {
  float *table = malloc(tableSize * sizeof(float));
  int i;
  for (i = 0; i < tableSize; i++) {
    table[i] = (2 / M_PI) * atan(tan((2 * M_PI * i) / (2 * tableSize)));
  }
  return table;
}

/*
Standar function to get interpolated values in table
*/
float mosaicsound_get_interpolated_freq(mosaicsound_osc_t *osc) {
  int my_floor = floor(osc->index);
  float y = osc->index - my_floor;
  float freqValue;

  if (osc->freq == NULL) {
    freqValue = osc->freqValue;
  } else
    freqValue = osc->freq[osc->index];

  /* Definition of circular indexes*/
  int index1 =
      (my_floor - 1 >= 0) ? my_floor - 1 : osc->tableSize + (my_floor - 1);
  int index2 = my_floor;
  int index3 = (my_floor + 1 < osc->tableSize) ? my_floor + 1
                                               : my_floor + 1 - osc->tableSize;
  int index4 = (my_floor + 2 < osc->tableSize) ? my_floor + 2
                                               : my_floor + 2 - osc->tableSize;

  float v_interpolado = -((y) * (y - 1) * (y - 2) * osc->table[index1]) /
                            6 /* CUBIC INTERPOLATION*/
                        +
                        ((y + 1) * (y - 1) * (y - 2) * osc->table[index2]) / 2 -
                        ((y + 1) * (y) * (y - 2) * osc->table[index3]) / 2 +
                        ((y + 1) * (y) * (y - 1) * osc->table[index4]) / 6;

  /* Next index to be read for this frequency*/
  osc->index += osc->tableSize * freqValue / osc->sampleRate;
  if (osc->index >= osc->tableSize) /* Truncation by the table size*/
    osc->index -= osc->tableSize;

  return v_interpolado;
}
