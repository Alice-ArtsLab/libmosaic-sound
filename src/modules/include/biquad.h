typedef struct {
    int type; /*0: Allpass; 1: Lowpass; 2: Highpass; 3: Bandpass; 4: Bandreject*/
    int order; /*1: First-order; 2: Second-order*/
    float *input;
    float *output;
    int framesPerBuffer;
    float sampleRate;
    float slope;
    float cutOff;
    float xn1; /* x(n-1) */
    float xn2; /* x(n-2) */
    float yn1; /* y(n-1) */
    float yn2; /* y(n-2) */
    void (*process)(void *self);
}biquad_t;

biquad_t *create_biquad(int type, int order, int framesPerBuffer);

void allpass_process();
void lowpass_process();
void highpass_process();
void bandpass_process();
void bandreject_process();
