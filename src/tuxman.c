#include "../include/functions.h"
#include "../include/menu_system.h"
#include "../include/game_loop.h"
#include "../include/init.h"
#include "../include/game_data.h"

int main ()
{
    initscr ();

    set_all_colors ();

    struct Game_Options game_info;
    struct Penguin tux;
    struct Game_States screen_data;                                             // data the gets displayed to screen
    game_info.open = 0;                                                               // used to insure the data is there

    get_screen_data (&screen_data, &game_info.open);

    game_info.wordCount = get_file_length ("data/words.txt", &game_info.open);                  //gets words used in program
    tux.words = (char**)malloc (game_info.wordCount * sizeof (char*));
    for (int i = 0; i < game_info.wordCount; i++)
    {
        tux.words[i] = malloc (SIZE * sizeof (char));
    }
    get_words ("data/words.txt", tux.words, &game_info.wordCount, &game_info.open);

    if (game_info.open == 0)
    {
        game_info.tux_win = newwin (28, 80, 0, 0);                                            // creates window but this is honestly pointless as I only use one in the entire program
        tux.option = '1';
        game_info.play = '0';
        game_info.welcome = '0';
        srand ( (time (NULL)));                                                     // seeds random number generator

        while (game_info.play == '0')                                  // menu loop
        {
            reset_game (&tux, &screen_data, &game_info);
            welcome_screen (&tux, &screen_data, &game_info);
            game_loop (&tux, &screen_data, &game_info);
            menu_system (&tux, &screen_data, &game_info);
        }
    }
    else
    {
        attron (COLOR_PAIR (2));
        printw ("\n   **ERROR**: The game files could not be found. Please reinstall the program.\n\n\n   Press enter to close the program...");
        getstr (tux.s_option);
    }

    free (tux.words);

    endwin ();

    return 0;
}
