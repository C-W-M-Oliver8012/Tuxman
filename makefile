# build an executable named myprog from myprog.c
all: tuxman.c
	gcc -Wall -o Tuxman tuxman.c

clean:
	$(RM) Tuxman
