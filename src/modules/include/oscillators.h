#ifndef MOSAICSOUND_OSCILLATORS_H
#define MOSAICSOUND_OSCILLATORS_H

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
    }mosaicsound_osc_t;

    mosaicsound_osc_t* mosaicsound_create_osc(int type, int framesPerBuffer, float tableSize);
    void mosaicsound_osc_process();

    float * mosaicsound_create_sine_table(int size);
    float * mosaicsound_create_square_table(int size);
    float * mosaicsound_create_triangle_table(int size);
    float * mosaicsound_create_sawtooth_table(int size);
    float mosaicsound_get_interpolated_freq(mosaicsound_osc_t *osc);

#endif /* oscillators.h */
