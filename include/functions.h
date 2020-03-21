#ifndef FUNCTIONS
#define FUNCTIONS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <curses.h>
#include "game_data.h"

void file_to_str (const char *filename, char *file_data, int *open);
int get_file_length (const char *filename, int *open);
void get_words (const char *filename, char **words, int *wordCount, int *open);
void correct_guesses_to_str (const struct Penguin *tux, char *screen);
void failed_guesses_to_str (const struct Penguin *tux, char *screen);
int check_guess_is_valid (const struct Penguin *tux);
int check_guess (const struct Penguin *tux);
int has_won (const struct Penguin *tux);
int check_full_guess (const struct Penguin *tux);
int add_score (const struct Penguin *tux);
void print_str (const char *str, const int color);
void print_game_scr (const long unsigned int *score, const long unsigned int *lives, const char *screen, const int *color_option);

#endif
