CC = gcc
CFLAGS = -Wall

default: all 

all: src/functions.c src/tuxman.c headers/functions.h
	$(CC) $(CFLAGS) -c src/functions.c
	$(CC) $(CFLAGS) -c src/tuxman.c
	$(CC) $(CFLAGS) -o Tuxman tuxman.o functions.o

functions: src/functions.c headers/functions.h
	$(CC) $(CFLAGS) -c src/functions.c

tuxman: src/tuxman.c headers/functions.h
	$(CC) $(CFLAGS) -c src/tuxman.c

Tuxman: src/tuxman.c src/functions.c headers/functions.h
	$(CC) $(CFLAGS) -o Tuxman tuxman.o functions.o

clean:
	$(RM) Tuxman *.o *~