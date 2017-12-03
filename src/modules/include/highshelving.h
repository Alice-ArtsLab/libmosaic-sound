#ifndef MOSAICSOUND_HIGHSHELVING_H
#define MOSAICSOUND_HIGHSHELVING_H

    typedef struct {
        float *input;
        float *output;
        float gain;
        int framesPerBuffer;
        float sampleRate;
        float cutOff;
        float xn1; /* x(n-1) */
        float xn2; /* x(n-2) */
        float yn1; /* y(n-1) */
        float yn2; /* y(n-2) */
        void (*process)(void *self);
    }mosaicsound_highshelving_t;

    mosaicsound_highshelving_t *mosaicsound_create_highshelving(int framesPerBuffer);
    void mosaicsound_highshelving_process();

#endif /* highshelving.h */
