typedef struct {
    int framesPerBuffer;
    int sampleRate;
    int paused; /* 0: paused ; 1: playing*/
    int time;
    int currentTime;
    int writeCount;
    float *input;
    void *sf;
    void (*process)(void *self);
    char *filename;
}record_t;

record_t *create_record(char *filename, int framesPerBuffer, int fTime, int sr);

void record_process();
void finished();
