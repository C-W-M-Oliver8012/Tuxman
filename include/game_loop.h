#ifndef GAME_LOOP
#define GAME_LOOP

#include "functions.h"
#include "game_data.h"

void set_category (Penguin *tux, Game_States *screen_data, Game_Options *game_info, Categories *categories);
void reset_game (Penguin *tux, Game_States *screen_data, Game_Options *game_info, Categories *categories);
void game_loop (Penguin *tux, Game_States *screen_data, Game_Options *game_info);
void get_screen_by_fails (Game_States *screen_data, long unsigned int *fails, int *color_option);
void guess_entire_word (Penguin *tux, const char *screen, const int *set_color);
void guess_single_char (Penguin *tux, const char *screen, const int *set_color);
void check_exit_game (const char *choice, long unsigned int *fails, long unsigned int *option);
void set_win (Penguin *tux, Game_States *screen_data, int *color_option);

#endif
