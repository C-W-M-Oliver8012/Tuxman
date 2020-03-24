#ifndef MENU_SYSTEM
#define MENU_SYSTEM

#include "functions.h"
#include "game_data.h"

void welcome_screen (Penguin *tux, Game_States *screen_data, const Game_Options *game_info);
void menu_system (Penguin *tux, Game_States *screen_data, Game_Options *game_info);
void game_over_screen (Penguin *tux, Game_States *screen_data, Game_Options *game_info);
void play_again_prompt (Penguin *tux, Game_States *screen_data, Game_Options *game_info);
void about_screen (Game_States *screen_data, Game_Options *game_info);
void return_to_menu_screen (Penguin *tux, char *screen, Game_Options *game_info);
void check_response (char *s_play, int *play, int *welcome, int display_welcome_screen, int no_option);

#endif
