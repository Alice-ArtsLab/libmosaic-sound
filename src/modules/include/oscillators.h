#ifndef OSCILLATORS_H
#define OSCILLATORS_H

    typedef struct {
        float *table;
        int tableSize;
        int index;
        int type; /*0: Sine; 1: Square; 2: Triangle; 3: Sawtooth.*/
        float freqValue;
        float *freq;
        float *output;
        int framesPerBuffer;
        float sampleRate;
        void (*process)(void *self);
    }osc_t;

    osc_t* create_osc(int type, int framesPerBuffer, float tableSize);
    void osc_process();

    float * create_sine_table(int size);
    float * create_square_table(int size);
    float * create_triangle_table(int size);
    float * create_sawtooth_table(int size);
    float get_interpolated_freq(osc_t *osc);

#endif /* oscillators.h */
