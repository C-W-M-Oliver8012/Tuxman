#ifndef INIT
#define INIT

#include "functions.h"
#include "game_data.h"

void set_all_colors (int *set_color);
void get_screen_data (Game_States *screen, int *open);
void init_words (Penguin *tux, Game_States *screen_data, Game_Options *game_info, Categories *categories);

#endif
