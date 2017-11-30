#ifndef SPEAKER_H
#define SPEAKER_H
    typedef struct {
        float *input;
        int framesPerBuffer;
        void (*process)(void *self, float *);
    }speaker_t;

    speaker_t* create_speaker(int framesPerBuffer);
    void speaker_process();
#endif /* speaker.h */
