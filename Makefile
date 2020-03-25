CC = gcc
CFLAGS = -Wall

default: linux

linux:
	$(CC) $(CFLAGS) -o tuxman src/tuxman.c src/functions.c src/macros.c src/init.c -lncurses

windows:
	$(CC) $(CFLAGS) -o tuxman.exe src/tuxman.c src/functions.c src/macros.c src/init.c pdcurses.a

clean:
	$(RM) tuxman tuxman.exe
