#include "../include/functions.h"
#include "../include/menu_system.h"
#include "../include/game_loop.h"
#include "../include/init.h"
#include "../include/game_data.h"

int main ()
{
    WINDOW *tux_win;
    tux_win = newwin (28, 80, 0, 0);                                            // creates window but this is honestly pointless as I only use one in the entire program

    srand ( (time (NULL)));                                                     // seeds random number generator

    initscr ();

    set_all_colors ();

    char s_play[SIZE];                                                           // controls the mean loop of the program
    char play = '0';
    char welcome = '0';

    struct Game_States screen_data;                                             // data the gets displayed to screen
    int open = 0;                                                               // used to insure the data is there

    get_screen_data (&screen_data, &open);

    int wordCount = get_file_length ("data/words.txt", &open);                  //gets words used in program
    char **words = (char**)malloc (wordCount * sizeof (char*));
    for (int i = 0; i < wordCount; i++)
    {
        words[i] = malloc (SIZE * sizeof (char));
    }
    get_words ("data/words.txt", words, &wordCount, &open);

    int pickLine, color_option;                                                 // used throughout program

    struct Penguin tux;
    tux.option = '1';

    if (open == 0)
    {
        while (play == '0')                                  // menu loop
        {
            reset_game (&tux, &screen_data, words, &pickLine, &wordCount);
            welcome_screen (&tux, &screen_data, tux_win, &welcome);
            game_loop (&tux, &screen_data, tux_win, &color_option);
            menu_system (&tux, &screen_data, &color_option, s_play, &play, &welcome, tux_win);
        }
    }
    else
    {
        attron (COLOR_PAIR (2));
        printw ("\n   **ERROR**: The game files could not be found. Please reinstall the program.\n\n\n   Press enter to close the program...");
        getstr (tux.s_option);
    }

    free (words);

    endwin ();

    return 0;
}
