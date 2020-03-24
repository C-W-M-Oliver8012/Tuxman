#include "../include/functions.h"
#include "../include/menu_system.h"
#include "../include/game_loop.h"
#include "../include/init.h"
#include "../include/game_data.h"


int main (void)
{
    Game_Options game_info;
    Penguin tux;
    Game_States screen_data;
    Categories categories;

    game_info.did_open = TRUE;

    initscr ();
    set_all_colors (&game_info.set_color);
    get_screen_data (&screen_data, &game_info.did_open);
    init_words (&tux, &screen_data, &game_info, &categories);

    if (game_info.did_open == TRUE)
    {
        tux.option = GAME_SCREEN;
        game_info.play = TRUE;
        game_info.welcome = TRUE;
        srand ( (time (NULL)));

        prompt_to_change_screen_size (screen_data.str11, &game_info.set_color);

        while (game_info.play == TRUE)
        {
            welcome_screen (&tux, &screen_data, &game_info);
            set_category (&tux, &screen_data, &game_info, &categories);
            reset_game (&tux, &screen_data, &game_info, &categories);
            game_loop (&tux, &screen_data, &game_info);
            menu_system (&tux, &screen_data, &game_info);
        }
    }
    else
    {
        if (game_info.set_color == TRUE)
        {
            attron (COLOR_PAIR (RED_PAIR));
        }
        printw ("\n   **ERROR**: The game files could not be found. Please reinstall the program.\n\n\n   Press enter to close the program...");
        getstr (tux.s_option);
    }

    free (tux.words);
    free (categories.filename);
    free (categories.description);
    free (categories.word_count);

    endwin ();

    return 0;
}
