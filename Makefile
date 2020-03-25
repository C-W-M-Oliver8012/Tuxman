CC = gcc
CFLAGS = -Wall

default: linux

linux:
	$(CC) $(CFLAGS) -o tuxman src/main.c src/functions.c -lncurses

windows:
	$(CC) $(CFLAGS) -o tuxman.exe src/main.c src/functions.c pdcurses.a

clean:
	$(RM) tuxman tuxman.exe
