#include <sndfile.h>

typedef struct {
    int loop;
    int channels;
    int framesPerBuffer;
    int fileSampleRate;
    int fileFrames;
    int readCount;
    int paused; /* 0: paused ; 1: playing*/
    float *outputL;
    float *outputR;
    float *input;
    char *filename;
    void (*process)(void *self);
}playback_t;

playback_t *create_playback(char *filename, int framesPerBuffer);

void playback_process_mono();
void playback_process_stereo();
