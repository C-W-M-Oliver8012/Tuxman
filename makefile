CC = gcc
CFLAGS = -Wall

default: linux

linux: src/functions.c src/tuxman.c headers/functions.h
	$(CC) $(CFLAGS) -o Tuxman.out src/tuxman.c src/functions.c -lncurses

windows:
	$(CC) $(CFLAGS) -o Tuxman.exe src/tuxman.c src/functions.c pdcurses.a

clean:
	$(RM) Tuxman.out Tuxman.exe
