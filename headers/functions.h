#ifndef FUNCTIONS
#define FUNCTIONS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <curses.h>

#define SIZE 256
#define INPUT_SIZE 2

struct Penguin
{
    char word[SIZE], index[SIZE], failedGuesses[SIZE], s_option[SIZE], option, s_choice[SIZE], choice;
    int wordLength, fails, indexLength, win, letters_guessed;
};

// PRINTS GRAPHICS FILES
void print_file(char *filename);
// RANDOMLY DETERMINES WHICH WORD TO SELECT FROM FILE
void get_word(char *word);
// PRINTS THE LETTERS GUESSED CORECTLY
void print_guess(struct Penguin *tux);
// PRINTS FAILED GUESSES
void print_failed_guesses(struct Penguin *tux);
// GETS GUESS AND ADDS TO INDEX IF NEEDED
void get_guess(struct Penguin *tux);
// DETERMINES IF PLAYER HAS WON
void has_won(struct Penguin *tux);
// CHECKS IF PLAYER WANTS TO EXIT THE GAME
void exit_game(struct Penguin *tux);

#endif
