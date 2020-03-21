#ifndef MENU_SYSTEM
#define MENU_SYSTEM

#include "functions.h"
#include "game_data.h"

void welcome_screen (struct Penguin *tux, struct Game_States *screen_data, const struct Game_Options *game_info);
void menu_system (struct Penguin *tux, struct Game_States *screen_data, struct Game_Options *game_info);
void game_over_screen (struct Penguin *tux, struct Game_States *screen_data, struct Game_Options *game_info);
void play_again_prompt (struct Penguin *tux, struct Game_States *screen_data, struct Game_Options *game_info);
void about_screen (struct Game_States *screen_data, struct Game_Options *game_info);
void return_to_menu_screen (struct Penguin *tux, char *screen, struct Game_Options *game_info);
void check_response (char *s_play, int *play, int *welcome, int display_welcome_screen, int no_option);

#endif
