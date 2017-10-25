typedef struct {
    int framesPerBuffer;
    int readCount;
    float *input;
    float *output;
    char *filename;
    char type; /* r: read; w: write. */
    void (*process)(void *self);
    /* Used to read and write sound files */
    void * infile;
    void * outfile;
    void *sfinfo;
    int finished;
}sndfile_t;

sndfile_t *create_sndfile(char type, char *filename, int framesPerBuffer);

void sndfile_write_process();
void sndfile_read_process();
