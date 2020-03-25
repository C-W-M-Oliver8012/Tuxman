/*
MIT License

Copyright (c) 2020 Caden Wayne Miller

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

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
