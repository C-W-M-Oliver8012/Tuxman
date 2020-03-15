#ifndef FUNCTIONS
#define FUNCTIONS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <curses.h>

#define SIZE 256
#define DATA_SIZE 12800
#define INPUT_SIZE 2

struct Penguin
{
    char word[SIZE], index[SIZE], failedGuesses[SIZE], s_option[SIZE], option, s_choice[SIZE], choice;
    unsigned long int wordLength, fails, indexLength, win, letters_guessed, score, max_score, lives;
};

// PRINTS GRAPHICS FILES
void get_file_data(char *filename, char *file_data);
// RANDOMLY DETERMINES WHICH WORD TO SELECT FROM FILE
void get_word(char *word);
// PRINTS THE LETTERS GUESSED CORECTLY
void correct_guesses_to_str(struct Penguin *tux, char *guess_data);
// PRINTS FAILED GUESSES
void failed_guesses_to_str(struct Penguin *tux, char *guess_data);
// GETS GUESS AND ADDS TO INDEX IF NEEDED
int check_guess(struct Penguin *tux);
// DETERMINES IF PLAYER HAS WON
int has_won(struct Penguin *tux);
int check_full_guess(struct Penguin *tux);
int add_score(struct Penguin *tux);

#endif
