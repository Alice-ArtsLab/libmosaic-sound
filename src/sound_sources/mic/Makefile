CC = gcc

CFLAGS = ../../lib/libportaudio.a -lrt -lm -lasound -ljack -pthread
OBJS =

TARGET = mic

all: $(TARGET)

%: %.c
	$(CC) $<  $(CFLAGS) -o $@

clean:
	rm -rf $(TARGET)
