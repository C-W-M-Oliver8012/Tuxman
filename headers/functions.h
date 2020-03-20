#ifndef FUNCTIONS
#define FUNCTIONS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <curses.h>

#define SIZE 256
#define DATA_SIZE 12800
#define WORD_SIZE 12800
#define INPUT_SIZE 2
#define COLOR_BROWN 10
#define COLOR_LBLUE 11

struct Penguin
{
    char word[SIZE], index[SIZE], failedGuesses[SIZE], s_option[SIZE], option, s_choice[SIZE], choice;
    unsigned long int wordLength, fails, indexLength, win, letters_guessed, score, max_score, lives;
};

struct Game_States
{
    char screen[DATA_SIZE];
    char str0[DATA_SIZE];
    char str1[DATA_SIZE];
    char str2[DATA_SIZE];
    char str3[DATA_SIZE];
    char str4[DATA_SIZE];
    char str5[DATA_SIZE];
    char str6[DATA_SIZE];
    char str7[DATA_SIZE];
    char str8[DATA_SIZE];
    char str9[DATA_SIZE];
    char str10[DATA_SIZE];
};

void file_to_str (char *filename, char *file_data, int *open);
int get_file_length (char *name, int *open);
void get_words (char *file_name, char **words, int *wordCount, int *open);
void correct_guesses_to_str (struct Penguin *tux, char *guess_data);
void failed_guesses_to_str (struct Penguin *tux, char *guess_data);
int check_guess_is_valid (struct Penguin *tux);
int check_guess (struct Penguin *tux);
int has_won (struct Penguin *tux);
int check_full_guess (struct Penguin *tux);
int add_score (struct Penguin *tux);
void print_str (char *str, int color);

#endif
