#ifndef PARAMETRIC_EQUALIZER_H
#define PARAMETRIC_EQUALIZER_H

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
    }parametric_eq_t;

    parametric_eq_t *create_parametric_eq(int framesPerBuffer);
    void parametric_eq_process();

#endif /* parametric_equalizer.h */
