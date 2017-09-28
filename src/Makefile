CC := gcc
CFLAGS := -g -Wall
LIBS := -lportaudio
OBJS := main.o list.o devices.o
TARGET := main
all: $(TARGET)

main: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o main $(LIBS)

list.o: util/list.c util/include/list.h
	$(CC) $(CFLAGS) -c util/list.c

devices.o: general/devices.c general/include/devices.h util/include/list.h
	$(CC) $(CFLAGS) -c general/devices.c $(LIBS)

clean:
	rm -rf $(OBJS) main
