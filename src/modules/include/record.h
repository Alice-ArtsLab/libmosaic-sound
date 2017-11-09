typedef struct {
    int framesPerBuffer;
    int paused; /* 0: paused ; 1: playing*/
    float *input;
    void (*process)(void *self);
    char *filename;
}record_t;

record_t *create_record(char *filename, int framesPerBuffer);

void record_process();
