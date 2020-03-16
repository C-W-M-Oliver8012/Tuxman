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

void file_to_str (char *filename, char *file_data);
void get_word (char *word);
void correct_guesses_to_str (struct Penguin *tux, char *guess_data);
void failed_guesses_to_str (struct Penguin *tux, char *guess_data);
int check_guess_is_valid (struct Penguin *tux);
int check_guess (struct Penguin *tux);
int has_won (struct Penguin *tux);
int check_full_guess (struct Penguin *tux);
int add_score (struct Penguin *tux);
void print_str (char *str, int color);

#endif
