CC := gcc
CFLAGS := -g -Wall
LIBS := -lportaudio -lm
OBJS := main.o list.o devices.o whitenoise.o audiomath.o oscillators.o mic.o \
biquad.o parametricequalizer.o lowshelving.o highshelving.o

TARGET := main
all: $(TARGET)

main: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o main $(LIBS)

list.o: util/list.c util/include/list.h
	$(CC) $(CFLAGS) -c util/list.c

devices.o: modules/devices.c modules/include/devices.h util/include/list.h
	$(CC) $(CFLAGS) -c modules/devices.c

whitenoise.o: modules/whitenoise.c modules/include/whitenoise.h
	$(CC) $(CFLAGS) -c modules/whitenoise.c

audiomath.o: modules/audiomath.c modules/include/audiomath.h
	$(CC) $(CFLAGS) -c modules/audiomath.c

oscillators.o: modules/oscillators.c modules/include/oscillators.h
	$(CC) $(CFLAGS) -c modules/oscillators.c

mic.o: modules/mic.c modules/include/mic.h
	$(CC) $(CFLAGS) -c modules/mic.c

biquad.o: modules/biquad.c modules/include/biquad.h
		$(CC) $(CFLAGS) -c modules/biquad.c

parametricequalizer.o: modules/parametricequalizer.c modules/include/parametricequalizer.h
		$(CC) $(CFLAGS) -c modules/parametricequalizer.c

lowshelving.o: modules/lowshelving.c modules/include/lowshelving.h
		$(CC) $(CFLAGS) -c modules/lowshelving.c

highshelving.o: modules/highshelving.c modules/include/highshelving.h
		$(CC) $(CFLAGS) -c modules/highshelving.c
clean:
	rm -rf $(OBJS) main
