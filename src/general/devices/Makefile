CC = gcc

CFLAGS = ../../lib/libportaudio.a -lrt -lm -lasound -ljack -pthread
OBJS =

TARGET = devices

all: $(TARGET)

%: %.c
	$(CC) $<  $(CFLAGS) -o $@

clean:
	rm -rf $(TARGET)
