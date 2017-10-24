typedef struct {
    float *input;
    float *output;
    float gain;
    int framesPerBuffer;
    float sampleRate;
    float cutOff;
    float xn1; /* x(n-1) */
    float xn2; /* x(n-2) */
    float yn1; /* y(n-1) */
    float yn2; /* y(n-2) */
    void (*process)(void *self);
}lowshelving_t;

lowshelving_t *create_lowshelving(int framesPerBuffer);
void lowshelving_process();
