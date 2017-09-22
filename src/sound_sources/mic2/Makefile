CC = gcc

CFLAGS = ../../../lib/libportaudio.a -lrt -lm -lasound -ljack -pthread
OBJS =

TARGET = mic2

all: $(TARGET)

%: %.c
	$(CC) $<  $(CFLAGS) -o $@

clean:
	rm -rf $(TARGET)
