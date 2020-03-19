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
    char file_data[DATA_SIZE], str0[DATA_SIZE], str1[DATA_SIZE], str2[DATA_SIZE],
            str3[DATA_SIZE], str4[DATA_SIZE], str5[DATA_SIZE], str6[DATA_SIZE], str7[DATA_SIZE], str8[DATA_SIZE], str9[DATA_SIZE], str10[DATA_SIZE];

    file_to_str ("graphics/welcome.txt", str0);
    file_to_str ("graphics/tuxman0.txt", str1);
    file_to_str ("graphics/tuxman1.txt", str2);
    file_to_str ("graphics/tuxman2.txt", str3);
    file_to_str ("graphics/tuxman3.txt", str4);
    file_to_str ("graphics/tuxman4.txt", str5);
    file_to_str ("graphics/tuxman5.txt", str6);
    file_to_str ("graphics/tuxman6.txt", str7);
    file_to_str ("graphics/tuxman7.txt", str8);
    file_to_str ("graphics/tuxman8.txt", str9);
    file_to_str ("graphics/about.txt", str10);

    int wordCount = get_file_length ("data/words.txt");
    char **words = (char**)malloc (wordCount * sizeof (char*));
    for (int i = 0; i < wordCount; i++)
    {
        words[i] = malloc (SIZE * sizeof (char));
    }
    get_words ("data/words.txt", words, &wordCount);
    int pickLine, color_option;

    struct Penguin tux;

    while (play == '0')                                  // menu loop
    {
        strcpy (file_data, "");

        welcome_screen (&tux, file_data, str0, tux_win, &welcome);

        if (tux.option == '1')                          // gets random word 
        {
            pickLine = rand () % wordCount;
            strcpy (tux.word, words[pickLine]);
            strtok (tux.word, "\n");
        }
        tux.wordLength = strlen (tux.word);
        tux.fails = 0;
        tux.indexLength = 0;
        tux.win = 0;
        tux.letters_guessed = 0;
        strcpy (tux.s_choice, "");
        tux.choice = ' ';

        game_loop (&tux, file_data, str1, str2, str3, str4, str5, str6, str7, str8, tux_win, &color_option);

        menu_system (&tux, &color_option, file_data, s_play, &play, &welcome, tux_win, str9, str10);
    }

    free (words);

    endwin ();

    return 0;
}
