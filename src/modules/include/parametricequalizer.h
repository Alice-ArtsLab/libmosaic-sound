#ifndef MOSAICSOUND_PARAMETRIC_EQUALIZER_H
#define MOSAICSOUND_PARAMETRIC_EQUALIZER_H

    typedef struct {
        float *input;
        float *output;
        int framesPerBuffer;
        float sampleRate;
        float slope;
        float gain;
        float cutOff;
        float xn1; /* x(n-1) */
        float xn2; /* x(n-2) */
        float yn1; /* y(n-1) */
        float yn2; /* y(n-2) */
        void (*process)(void *self);
    }mosaicsound_parametric_eq_t;

    mosaicsound_parametric_eq_t *mosaicsound_create_parametric_eq(int framesPerBuffer);
    void mosaicsound_parametric_eq_process();

#endif /* parametric_equalizer.h */
