#ifndef MOSAICSOUND_RECORD_H
#define MOSAICSOUND_RECORD_H

    typedef struct {
        int framesPerBuffer;
        int sampleRate;
        int paused; /* 0: paused ; 1: playing*/
        int time;
        int currentTime;
        int writeCount;
        float *input0;
        void *sf;
        void (*process)(void *self);
        char *filename;
    }mosaicsound_record_t;

    mosaicsound_record_t *mosaicsound_create_record(char *filename, int framesPerBuffer, int fTime, int sr);

    void mosaicsound_record_process();
    void mosaicsound_record_finished();

#endif /* record.h */
