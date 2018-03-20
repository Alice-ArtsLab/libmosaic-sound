#ifndef MOSAICSOUND_WHITENOISE_H
#define MOSAICSOUND_WHITENOISE_H

    typedef struct {
        void (*process)(void *self);
        float *output0;
        int framesPerBuffer;
    }mosaicsound_noise_t;

    mosaicsound_noise_t* mosaicsound_create_noise(int framesPerBuffer);
    void mosaicsound_noise_process();

#endif /* whitenoise.h */
