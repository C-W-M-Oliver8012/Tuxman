CC = gcc
CFLAGS = -Wall

default: linux

linux:
	$(CC) $(CFLAGS) -o Tuxman src/tuxman.c src/functions.c src/menu_system.c src/game_loop.c src/init.c -lncurses

windows:
	$(CC) $(CFLAGS) -o Tuxman.exe src/tuxman.c src/functions.c src/menu_system.c src/game_loop.c src/init.c pdcurses.a

clean:
	$(RM) Tuxman Tuxman.exe
