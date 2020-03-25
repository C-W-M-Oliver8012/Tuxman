CC = gcc
CFLAGS = -Wall

default: linux

linux:
	$(CC) $(CFLAGS) -o tuxman src/tuxman.c src/functions.c src/macros.c -lncurses

windows:
	$(CC) $(CFLAGS) -o tuxman.exe src/tuxman.c src/functions.c src/macros.c pdcurses.a

clean:
	$(RM) tuxman tuxman.exe
