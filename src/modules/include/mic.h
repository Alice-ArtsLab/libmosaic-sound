#ifndef MIC_H
#define MIC_H
    typedef struct {
        float *output;
        int framesPerBuffer;
        void (*process)(void *self, float *);
    }mic_t;

    mic_t* create_mic(int framesPerBuffer);
    void mic_process();
#endif /* mic.h */
