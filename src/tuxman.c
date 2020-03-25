#include "../include/functions.h"
#include "../include/macros.h"
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
        tux.option = WELCOME_SCREEN;
        game_info.play = TRUE;
        srand ( (time (NULL)));

        prompt_to_change_screen_size (screen_data.str11, &game_info.set_color);

        while (game_info.play == TRUE)
        {
            switch (tux.option)
            {
                case WELCOME_SCREEN:
                    welcome_screen (&tux, &screen_data, &game_info);
                    break;
                case GAME_SCREEN:
                    set_category (&tux, &screen_data, &game_info, &categories);
                    reset_game (&tux, &screen_data, &game_info, &categories);
                    game_loop (&tux, &screen_data, &game_info);
                    if (tux.lives == 0)
                    {
                        game_over_screen (&tux, &screen_data, &game_info);
                        tux.option = WELCOME_SCREEN;
                    }
                    else if (tux.option == GAME_SCREEN)
                    {
                        play_again_prompt (&tux, &screen_data, &game_info);
                        tux.option = GAME_SCREEN;
                    }
                    break;
                case ABOUT_SCREEN:
                    about_screen (&screen_data, &game_info);
                    tux.option = WELCOME_SCREEN;
                    break;
                case QUIT_GAME:
                    game_info.play = FALSE;
                    break;
                case RETURN_TO_MENU_PROMPT:
                    return_to_menu_screen (&tux, screen_data.screen, &game_info);
                    tux.option = WELCOME_SCREEN;
            }
        }
    }
    else
    {
        set_color_if_possible (RED_PAIR, &game_info.set_color);
        printw ("\n   **ERROR**: The game files could not be found. Please reinstall the program.\n\n\n   Press enter to close the program...");
        getstr (tux.input);
    }

    free (tux.words);
    free (categories.filename);
    free (categories.description);
    free (categories.word_count);

    endwin ();

    return 0;
}
