#ifndef FUNCTIONS
#define FUNCTIONS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <curses.h>
#include "game_data.h"

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
void print_game_scr (long unsigned int *score, long unsigned int *lives, char *screen, int *color_option);

#endif
