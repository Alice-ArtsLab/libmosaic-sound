#include <sndfile.h>

typedef struct {
    int loop;
    int framesPerBuffer;
    int fileSampleRate;
    int fileFrames;
    int readCount;
    int paused; /* 0: paused ; 1: playing*/
    float *output;
    float *input;
    char *filename;
    void (*process)(void *self);
}playback_t;

playback_t *create_playback(char *filename, int framesPerBuffer);

void playback_process();
