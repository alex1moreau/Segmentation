CC=gcc
CFLAGS=-W -Wall -ansi -pedantic
LDFLAGS=
EXEC=main clean

all: $(EXEC)

main: main.o filter.o
	$(CC) -o main filter.o main.o $(LDFLAGS)

main.o: main.c filter.h
	$(CC) -o main.o -c main.c $(CFLAGS)

filter.o: filter.c
	$(CC) -o filter.o -c filter.c $(CFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
