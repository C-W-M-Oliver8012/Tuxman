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
void get_categories_filename_description (Categories *categories, int *did_open);
void get_words (const char *filename, char **words, int *wordCount, int *open);
int str_is_int (const char *str);
void correct_guesses_to_str (const Penguin *tux, char *screen);
void failed_guesses_to_str (const Penguin *tux, char *screen);
int check_guess_is_valid (const Penguin *tux);
int check_guess (const Penguin *tux);
int has_won (const Penguin *tux);
int check_full_guess (const Penguin *tux);
int add_score (const Penguin *tux);
void print_str (const char *str, const int color, const int *set_color);
void print_game_scr (const Penguin *tux, const char *screen, const int color_option, const int *set_color);
void set_color_if_possible (const int color, const int *set_color);
void print_str_between_two_colors (const int first_color, const int second_color, const char *str, const int *set_color);

#endif
