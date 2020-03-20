#ifndef MENU_SYSTEM
#define MENU_SYSTEM

#include "functions.h"

void print_game_scr (long unsigned int *score, long unsigned int *lives, char *screen, int *color_option);
void welcome_screen (struct Penguin *tux, struct Game_States *screen_data, WINDOW *tux_win, char *welcome);
void menu_system (struct Penguin *tux, struct Game_States *screen_data, int *color_option, char *s_play, char *play, char *welcome, WINDOW *tux_win);
void game_over_screen (struct Penguin *tux, struct Game_States *screen_data, char *play, char *welcome, char *s_play, int *color_option, WINDOW *tux_win);
void play_again_prompt (struct Penguin *tux, struct Game_States *screen_data, char *play, char *welcome, char *s_play, int *color_option, WINDOW *tux_win);
void about_screen (struct Game_States *screen_data, char *play, char *welcome, char *s_play, int *color_option, WINDOW *tux_win);
void return_to_menu_screen (struct Penguin *tux, char *screen, char *play, char *welcome, char *s_play, int *color_option, WINDOW *tux_win);
void check_response (char *s_play, char *play, char *welcome, char display_welcome_screen);

#endif
