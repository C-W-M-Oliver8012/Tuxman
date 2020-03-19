CC = gcc
CFLAGS = -Wall

default: linux

linux: src/functions.c src/tuxman.c headers/functions.h
	$(CC) $(CFLAGS) -o Tuxman.out src/tuxman.c src/functions.c src/menu_system.c src/game_loop.c -lncurses

windows:
	$(CC) $(CFLAGS) -o Tuxman.exe src/tuxman.c src/functions.c src/menu_system.c src/game_loop.c dcurses.a

clean:
	$(RM) Tuxman.out Tuxman.exe
