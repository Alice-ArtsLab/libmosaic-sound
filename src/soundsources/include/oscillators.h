#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#define TABLE_SIZE 2048

typedef struct t_data{
    float * table;
    float index;
}sine_data;


float *  create_sine_table(float * table);
float *  create_square_table(float * table);
float *  create_triangle_table(float * table);
float *  create_sawtooth_table(float * table);
float get_interpolated_freq(sine_data * data, float frequency, float sr);
