#ifndef MENU_SYSTEM
#define MENU_SYSTEM

#include "functions.h"

void print_game_scr (long unsigned int *score, long unsigned int *lives, char *file_data, int *color_option);
void welcome_screen (struct Penguin *tux, char *file_data, char *str0, WINDOW *tux_win, char *welcome);
void menu_system (struct Penguin *tux, int *color_option, char *file_data, char *s_play, char *play, char *welcome, WINDOW *tux_win, char *str9, char *str10);

#endif
