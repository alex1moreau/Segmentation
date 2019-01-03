CC=gcc
CFLAGS=-W -Wall -Wextra -std=c99
LDFLAGS=-lm `pkg-config --libs sdl` -lSDL_image
EXEC=main clean

all: $(EXEC)

main: main.o filter.o op.o
	$(CC) -o main filter.o op.o main.o $(LDFLAGS)

main.o: main.c filter.h op.h
	$(CC) -o main.o -c main.c $(CFLAGS)

filter.o: filter.c
	$(CC) -o filter.o -c filter.c $(CFLAGS)

op.o: op.c
	$(CC) -o op.o -c op.c $(CFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
