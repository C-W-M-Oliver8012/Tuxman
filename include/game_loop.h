#ifndef GAME_LOOP
#define GAME_LOOP

#include "functions.h"
#include "game_data.h"

void set_category (Penguin *tux, const Game_States *screen_data, Game_Options *game_info, Categories *categories);
void reset_game (Penguin *tux, Game_States *screen_data, Game_Options *game_info, Categories *categories);
void game_loop (Penguin *tux, Game_States *screen_data, Game_Options *game_info);
void get_screen_by_fails (Game_States *screen_data, int *fails, int *color_option);
void guess_entire_word (Penguin *tux, const int *set_color);
void guess_single_char (Penguin *tux, const int *set_color);
void check_if_player_has_lost (int *fails, int *win, int *option);
void check_exit_game (const char *choice, int *win, int *option);
void set_win (Penguin *tux, Game_States *screen_data, int *color_option);

#endif
