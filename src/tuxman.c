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
    game_info.did_open = TRUE;                                                               // used to insure the data is there

    get_screen_data (&screen_data, &game_info.did_open);

    game_info.wordCount = get_file_length ("data/words.txt", &game_info.did_open);                  //gets words used in program
    tux.words = (char**)malloc (game_info.wordCount * sizeof (char*));
    for (int i = 0; i < game_info.wordCount; i++)
    {
        tux.words[i] = malloc (SIZE * sizeof (char));
    }
    get_words ("data/words.txt", tux.words, &game_info.wordCount, &game_info.did_open);

    if (game_info.did_open == TRUE)
    {
        game_info.tux_win = newwin (28, 80, 0, 0);                                            // creates window but this is honestly pointless as I only use one in the entire program
        refresh ();
        tux.option = GAME_SCREEN;
        game_info.play = TRUE;
        game_info.welcome = TRUE;
        srand ( (time (NULL)));                                                     // seeds random number generator

        char temp[SIZE];
        do
            {
                clear ();
                print_str (screen_data.str11, 2);
                getstr (temp);
                if (strlen (temp) > INPUT_SIZE)
                {
                    strcpy (temp, " ");
                }
            }
        while(temp[0] != 'y');

        while (game_info.play == TRUE)                                  // menu loop
        {
            reset_game (&tux, &screen_data, &game_info);
            welcome_screen (&tux, &screen_data, &game_info);
            game_loop (&tux, &screen_data, &game_info);
            menu_system (&tux, &screen_data, &game_info);
        }
    }
    else
    {
        attron (COLOR_PAIR (RED_PAIR));
        printw ("\n   **ERROR**: The game files could not be found. Please reinstall the program.\n\n\n   Press enter to close the program...");
        getstr (tux.s_option);
    }

    free (tux.words);

    endwin ();

    return 0;
}
