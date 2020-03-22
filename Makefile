CC = gcc
CFLAGS = -Wall

default: linux

linux:
	$(CC) $(CFLAGS) -o tuxman src/tuxman.c src/functions.c src/menu_system.c src/game_loop.c src/init.c -lncurses

windows:
	$(CC) $(CFLAGS) -o tuxman.exe src/tuxman.c src/functions.c src/menu_system.c src/game_loop.c src/init.c pdcurses.a

clean:
	$(RM) tuxman tuxman.exe
