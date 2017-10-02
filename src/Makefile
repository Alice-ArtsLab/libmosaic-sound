CC := gcc
CFLAGS := -g -Wall
LIBS := -lportaudio -lm
OBJS := main.o list.o devices.o whitenoise.o audiomath.o oscillators.o mic.o
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
clean:
	rm -rf $(OBJS) main
