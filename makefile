CC = gcc
CFLAGS = -Wall

default: all

all: src/functions.c src/tuxman.c headers/functions.h
	$(CC) $(CFLAGS) -c src/functions.c
	$(CC) $(CFLAGS) -c src/tuxman.c
	# FOR LINUX
	$(CC) $(CFLAGS) -o Tuxman.out tuxman.o functions.o -lncurses
	# FOR WINDOWS
	# $(CC) $(CFLAGS) -o Tuxman tuxman.o functions.o pdcurses.a

functions: src/functions.c headers/functions.h
	$(CC) $(CFLAGS) -c src/functions.c

tuxman: src/tuxman.c headers/functions.h
	$(CC) $(CFLAGS) -c src/tuxman.c

Tuxman: src/tuxman.c src/functions.c headers/functions.h
	# FOR LINUX
	$(CC) $(CFLAGS) -o Tuxman.out tuxman.o functions.o -lncurses
	# FOR WINDOWS
	# $(CC) $(CFLAGS) -o Tuxman tuxman.o functions.o pdcurses.a

clean:
	# FOR LINUX
	$(RM) Tuxman.out *.o *~
	# FOR WINDOWS
	$(RM) Tuxman.exe *.o *~
