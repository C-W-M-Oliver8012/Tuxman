#include "../headers/functions.h"
#include "../headers/menu_system.h"
#include "../headers/game_loop.h"

int main ()
{
    WINDOW *tux_win;
    tux_win = newwin (28, 80, 0, 0);

    srand ( (time (NULL)));                             // seeds random number generator

    initscr ();

    start_color ();
    init_color (COLOR_BLACK, 25, 25, 25);
    init_color (COLOR_GREEN, 262, 690, 164);
    init_color (COLOR_RED, 933, 219, 192);
    init_color (COLOR_BLUE, 0, 490, 729);
    init_color (COLOR_YELLOW, 882, 835, 333);
    init_color (COLOR_WHITE, 850, 850, 850);
    init_color (COLOR_BROWN, 600, 400, 50);

    init_pair (1, COLOR_GREEN, COLOR_BLACK);
    init_pair (2, COLOR_RED, COLOR_BLACK);
    init_pair (3, COLOR_BLUE, COLOR_BLACK);
    init_pair (4, COLOR_YELLOW, COLOR_BLACK);
    init_pair (5, COLOR_WHITE, COLOR_BLACK);
    init_pair (6, COLOR_BROWN, COLOR_BLACK);
    init_pair (7, COLOR_LBLUE, COLOR_BLACK);

    char s_play[SIZE];
    char play = '0';
    char welcome = '0';
    struct Game_States screen_data;
    int open = 0;

    file_to_str ("graphics/welcome.txt", screen_data.str0, &open);
    file_to_str ("graphics/tuxman0.txt", screen_data.str1, &open);
    file_to_str ("graphics/tuxman1.txt", screen_data.str2, &open);
    file_to_str ("graphics/tuxman2.txt", screen_data.str3, &open);
    file_to_str ("graphics/tuxman3.txt", screen_data.str4, &open);
    file_to_str ("graphics/tuxman4.txt", screen_data.str5, &open);
    file_to_str ("graphics/tuxman5.txt", screen_data.str6, &open);
    file_to_str ("graphics/tuxman6.txt", screen_data.str7, &open);
    file_to_str ("graphics/tuxman7.txt", screen_data.str8, &open);
    file_to_str ("graphics/tuxman8.txt", screen_data.str9, &open);
    file_to_str ("graphics/about.txt", screen_data.str10, &open);

    int wordCount = get_file_length ("data/words.txt", &open);
    char **words = (char**)malloc (wordCount * sizeof (char*));
    for (int i = 0; i < wordCount; i++)
    {
        words[i] = malloc (SIZE * sizeof (char));
    }
    get_words ("data/words.txt", words, &wordCount, &open);
    int pickLine, color_option;

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
