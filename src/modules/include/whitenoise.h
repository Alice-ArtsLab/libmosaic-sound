#ifndef WHITENOISE_H
#define WHITENOISE_H

    typedef struct {
        void (*process)(void *self);
        float *output;
        int framesPerBuffer;
    }noise_t;

    noise_t* create_noise(int framesPerBuffer);
    void noise_process();

#endif /* whitenoise.h */
