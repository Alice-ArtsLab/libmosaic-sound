#include <sndfile.h>

typedef struct {
    int framesPerBuffer;
    int readCount;
    float *input;
    float *output;
    char type; /* r: read; w: write. */
    void (*process)(void *self);
    /* Used to read and write sound files */
    SNDFILE *sf;
    SF_INFO info;
    int finished;
    char *filename;
}sndfile_t;

sndfile_t *create_sndfile(char type, char *filename, int framesPerBuffer);

void sndfile_write_process();
void sndfile_read_process();
