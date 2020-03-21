#ifndef GAME_LOOP
#define GAME_LOOP

#include "functions.h"
#include "game_data.h"

void reset_game (struct Penguin *tux, struct Game_States *screen_data, char **words, int *pickLine, int *wordCount);
void game_loop (struct Penguin *tux, struct Game_States *screen_data, WINDOW *tux_win, int *color_option);
void get_screen_by_fails (struct Game_States *screen_data, long unsigned int *fails, int *color_option);
void guess_entire_word (struct Penguin *tux, char *screen, int *color_option, WINDOW *tux_win);
void guess_single_char (struct Penguin *tux, char *screen, int *color_option, WINDOW *tux_win);
void check_exit_game (char *choice, long unsigned int *fails, char *option);
void set_win (struct Penguin *tux, struct Game_States *screen_data, int *color_option);

#endif
