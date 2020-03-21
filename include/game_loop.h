#ifndef GAME_LOOP
#define GAME_LOOP

#include "functions.h"
#include "game_data.h"

void reset_game (struct Penguin *tux, struct Game_States *screen_data, struct Game_Options *game_info);
void game_loop (struct Penguin *tux, struct Game_States *screen_data, struct Game_Options *game_info);
void get_screen_by_fails (struct Game_States *screen_data, long unsigned int *fails, int *color_option);
void guess_entire_word (struct Penguin *tux, const char *screen, int *color_option, WINDOW *tux_win);
void guess_single_char (struct Penguin *tux, const char *screen, int *color_option, WINDOW *tux_win);
void check_exit_game (const char *choice, long unsigned int *fails, long unsigned int *option);
void set_win (struct Penguin *tux, struct Game_States *screen_data, int *color_option);

#endif
