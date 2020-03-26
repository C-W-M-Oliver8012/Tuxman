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
#include "../include/game_data.h"


void check_response (Penguin *tux, const int no_option);



int main (void)
{
    Penguin tux;
    Game_States screen_data;
    Categories categories;

    tux.did_open = TRUE;

    initscr ();

    if (has_colors () == TRUE)
    {
        start_color ();
        if (can_change_color () == TRUE)
        {
            init_color (COLOR_BLACK, 25, 25, 25);                                       // defines all colors used in program
            init_color (COLOR_GREEN, 262, 690, 164);
            init_color (COLOR_RED, 933, 219, 192);
            init_color (COLOR_BLUE, 0, 490, 729);
            init_color (COLOR_YELLOW, 882, 835, 333);
            init_color (COLOR_WHITE, 850, 850, 850);
            init_color (COLOR_BROWN, 600, 400, 50);
        }
        else
        {
            init_pair (BROWN_PAIR, COLOR_MAGENTA, COLOR_BLACK);
        }

        init_pair (GREEN_PAIR, COLOR_GREEN, COLOR_BLACK);                                    // cerates all color pairs used in program
        init_pair (RED_PAIR, COLOR_RED, COLOR_BLACK);
        init_pair (BLUE_PAIR, COLOR_BLUE, COLOR_BLACK);
        init_pair (YELLOW_PAIR, COLOR_YELLOW, COLOR_BLACK);
        init_pair (WHITE_PAIR, COLOR_WHITE, COLOR_BLACK);
        init_pair (BROWN_PAIR, COLOR_BROWN, COLOR_BLACK);

        tux.set_color = TRUE;
    }
    else
    {
        tux.set_color = FALSE;
    }

    file_to_str ("graphics/welcome.txt", screen_data.str0, &tux.did_open);              // gets screen data from files
    file_to_str ("graphics/tuxman0.txt", screen_data.str1, &tux.did_open);
    file_to_str ("graphics/tuxman1.txt", screen_data.str2, &tux.did_open);
    file_to_str ("graphics/tuxman2.txt", screen_data.str3, &tux.did_open);
    file_to_str ("graphics/tuxman3.txt", screen_data.str4, &tux.did_open);
    file_to_str ("graphics/tuxman4.txt", screen_data.str5, &tux.did_open);
    file_to_str ("graphics/tuxman5.txt", screen_data.str6, &tux.did_open);
    file_to_str ("graphics/tuxman6.txt", screen_data.str7, &tux.did_open);
    file_to_str ("graphics/tuxman7.txt", screen_data.str8, &tux.did_open);
    file_to_str ("graphics/tuxman8.txt", screen_data.str9, &tux.did_open);
    file_to_str ("graphics/about.txt", screen_data.str10, &tux.did_open);
    file_to_str ("graphics/win_resize.txt", screen_data.str11, &tux.did_open);
    file_to_str ("graphics/choose_categories.txt", screen_data.str12, &tux.did_open);

    categories.category_count = get_file_length ("data/categories.txt", &tux.did_open);
    categories.filename = (char**)malloc (categories.category_count * sizeof (char*));
    categories.description = (char**)malloc (categories.category_count * sizeof (char*));
    categories.word_count = (int*)malloc (categories.category_count * sizeof (int));
    for (int i = 0; i < categories.category_count; i++)
    {
        categories.filename[i] = malloc (SIZE * sizeof (char));
        categories.description[i] = malloc (SIZE * sizeof (char));
    }
    get_categories_filename_description (&categories, &tux.did_open);
    categories.max_word_count = 0;
    for (int i = 0; i < categories.category_count; i++)
    {
        char temp_dir[NAME_SIZE];
        strcpy (temp_dir, "data/");
        strcat (temp_dir, categories.filename[i]);
        strcat (temp_dir, ".txt");
        categories.word_count[i] = get_file_length (temp_dir, &tux.did_open);
        if (categories.word_count[i] > categories.max_word_count)
        {
            categories.max_word_count = categories.word_count[i];
        }
    }

    tux.words = (char***)malloc (categories.category_count * sizeof (char**));
    for (int i = 0; i < categories.category_count; i++)
    {
        tux.words[i] = (char**)malloc (categories.max_word_count * sizeof (char*));
        for (int j = 0; j < categories.max_word_count; j++)
        {
            tux.words[i][j] = malloc (SIZE * sizeof (char));
        }
    }
    for (int i = 0; i < categories.category_count; i++)
    {
        char temp_dir[NAME_SIZE];
        strcpy (temp_dir, "data/");
        strcat (temp_dir, categories.filename[i]);
        strcat (temp_dir, ".txt");
        get_words (temp_dir, tux.words[i], &categories.word_count[i], &tux.did_open);
    }

    if (tux.did_open == TRUE)
    {
        tux.option = WELCOME_SCREEN;
        tux.play = TRUE;
        mysrand ( (time (NULL)));

        char input[SIZE];
        do
            {
                clear ();
                print_str (screen_data.str11, BROWN_FOR_MENU_SCREENS, &tux.set_color);
                print_str_between_two_colors (GREEN_PAIR, WHITE_PAIR, " Enter 'y' here: ", &tux.set_color);
                getstr (input);

                if (strlen (input) > INPUT_SIZE)
                {
                    strcpy (input, " ");
                }
            }
        while(input[0] != 'y');

        while (tux.play == TRUE)
        {
            switch (tux.option)
            {
                case WELCOME_SCREEN:
                    tux.score = 0;
                    tux.lives = 5;
                    tux.max_score = 10;
                    tux.category_has_been_set = FALSE;

                    do
                        {
                            clear ();
                            print_str (screen_data.str0, BROWN_FOR_MENU_SCREENS, &tux.set_color);
                            print_str_between_two_colors (GREEN_PAIR, WHITE_PAIR, "\n   Option: ", &tux.set_color);
                            getstr (tux.input);

                            if (strlen (tux.input) < INPUT_SIZE)
                            {
                                switch (tux.input[0])
                                {
                                    case '1':
                                        tux.option = GAME_SCREEN;
                                        break;
                                    case '2':
                                        tux.option = ABOUT_SCREEN;
                                        break;
                                    case '3':
                                        tux.option = QUIT_GAME;
                                        break;
                                    default:
                                        tux.option = INCORRECT_INPUT;
                                }
                            }
                            else
                            {
                                tux.option = INCORRECT_INPUT;
                            }
                        }
                    while(tux.option == INCORRECT_INPUT);
                    break;



                case GAME_SCREEN:
                    if (tux.category_has_been_set == FALSE)
                    {
                        do
                            {
                                tux.category_choice = -1;

                                clear ();
                                print_str (screen_data.str12, BROWN_FOR_MENU_SCREENS, &tux.set_color);
                                set_color_if_possible (WHITE_PAIR, &tux.set_color);

                                for (int i = 0; i < categories.category_count; i++)
                                {
                                    print_str_between_two_colors (BROWN_PAIR, WHITE_PAIR, "   |", &tux.set_color);
                                    printw (" %2d) %-39s", i+1, categories.description[i]);
                                    set_color_if_possible (BROWN_PAIR, &tux.set_color);
                                    printw (" |\n");
                                }

                                print_str_between_two_colors (BROWN_PAIR, GREEN_PAIR, "   ===============================================\n", &tux.set_color);
                                printw ("\n   Category option: ");
                                set_color_if_possible (WHITE_PAIR, &tux.set_color);
                                getstr (tux.input);

                                if (strlen (tux.input) < 4)
                                {
                                    if (str_is_int (tux.input) == TRUE)
                                    {
                                        tux.category_choice = strtol (tux.input, NULL, 10);
                                    }
                                }
                                else
                                {
                                    tux.category_choice = -1;
                                }

                                tux.category_choice--;
                            }
                        while((tux.category_choice < 0) || (tux.category_choice > 24) || (tux.category_choice >= categories.category_count));

                        tux.category_has_been_set = TRUE;
                    }



                    strcpy (screen_data.screen, "");
                    tux.pickLine = myrand () % categories.word_count[tux.category_choice];
                    strcpy (tux.word, tux.words[tux.category_choice][tux.pickLine]);
                    strtok (tux.word, "\n");
                    tux.wordLength = strlen (tux.word);
                    tux.indexLength = 0;
                    tux.letters_guessed = 0;
                    tux.choice = ' ';
                    tux.fails = 0;
                    tux.win = NOT_FALSE_OR_TRUE;



                    while (tux.win == NOT_FALSE_OR_TRUE)
                    {
                        clear ();
                        strcpy (screen_data.screen, "");

                        switch (tux.fails)                          // GETS PROPER GRAPHIC TO PRINT
                        {

                            case 0:
                                strcat (screen_data.screen, screen_data.str1);
                                break;
                            case 1:
                                strcat (screen_data.screen, screen_data.str2);
                                break;
                            case 2:
                                strcat (screen_data.screen, screen_data.str3);
                                break;
                            case 3:
                                strcat (screen_data.screen, screen_data.str4);
                                break;
                            case 4:
                                strcat (screen_data.screen, screen_data.str5);
                                break;
                            case 5:
                                strcat (screen_data.screen, screen_data.str6);
                                break;
                        }

                        correct_guesses_to_str (&tux, screen_data.screen);
                        failed_guesses_to_str (&tux, screen_data.screen);

                        if (tux.win == NOT_FALSE_OR_TRUE)
                        {
                            print_game_scr (&tux, screen_data.screen, BLUE_FOR_PENGUIN, &tux.set_color);

                            if (tux.choice == '@')
                            {
                                print_str_between_two_colors (GREEN_PAIR, WHITE_PAIR, "\n   Guess the word: ", &tux.set_color);
                                getstr (tux.input);

                                tux.win = check_full_guess (&tux);
                                if (tux.win == NOT_FALSE_OR_TRUE)
                                {
                                    tux.failedGuesses[tux.fails] = '@';
                                    tux.fails = tux.fails + 1;
                                    tux.choice = ' ';
                                }
                                else if (tux.win == TRUE)
                                {
                                    for (int i = 0; i < tux.wordLength; i++)
                                    {
                                        int matched = 0;

                                        for (int j = 0; j < tux.indexLength; j++)
                                        {
                                            if ( (tux.word[i] == tux.index[j]) || (tux.word[i] == ' '))
                                            {
                                                matched = 1;
                                            }
                                        }

                                        if (matched == 0)
                                        {
                                            tux.index[tux.indexLength] = tux.word[i];
                                            tux.indexLength++;
                                        }
                                    }
                                }
                                if (tux.fails == 6)
                                {
                                    tux.win = FALSE;
                                    tux.option = GAME_SCREEN;
                                }
                            }
                            else
                            {
                                print_str_between_two_colors (GREEN_PAIR, WHITE_PAIR, "\n   Pick a letter: ", &tux.set_color);
                                getstr (tux.input);

                                if (strlen (tux.input) < INPUT_SIZE)
                                {
                                    tux.choice = tux.input[0];
                                    int valid;
                                    if (check_guess_is_valid (&tux) == TRUE)
                                    {
                                        valid = check_guess (&tux);
                                    }
                                    else
                                    {
                                        valid = NOT_FALSE_OR_TRUE;
                                    }
                                    if (valid == FALSE)
                                    {
                                        tux.failedGuesses[tux.fails] = tux.choice;
                                        tux.fails++;
                                    }
                                    else if (valid == TRUE)
                                    {
                                        tux.index[tux.indexLength] = tux.choice;
                                        tux.indexLength++;
                                    }

                                    tux.win = has_won (&tux);
                                }
                                if (tux.fails == 6)
                                {
                                    tux.win = FALSE;
                                    tux.option = GAME_SCREEN;
                                }
                                if (tux.choice == '^')
                                {
                                    tux.win = FALSE;
                                    tux.option = RETURN_TO_MENU_PROMPT;
                                }
                            }
                        }

                        if ((tux.win == FALSE) && (tux.option == GAME_SCREEN))
                        {
                            strcpy (screen_data.screen, "");
                            strcat (screen_data.screen, screen_data.str7);
                            correct_guesses_to_str (&tux, screen_data.screen);
                            failed_guesses_to_str (&tux, screen_data.screen);
                            tux.color_option = 4;
                            tux.lives--;
                        }

                        if (tux.win == TRUE)
                        {
                            strcpy (screen_data.screen, "");
                            int add = add_score (&tux);
                            tux.score = tux.score + add;
                            int diff = tux.score - tux.max_score;
                            while (diff >= 10)
                            {
                                tux.lives++;
                                tux.max_score = tux.max_score + 10;
                                diff = tux.score - tux.max_score;
                            }
                            if (tux.score >= tux.max_score)
                            {
                                tux.lives++;
                                tux.max_score = tux.max_score + 10;
                            }
                            strcat (screen_data.screen, screen_data.str8);
                            correct_guesses_to_str (&tux, screen_data.screen);
                            failed_guesses_to_str (&tux, screen_data.screen);
                            tux.color_option = 3;
                        }
                    }
                    if (tux.lives == 0)
                    {
                        strcpy (screen_data.screen, "");
                        strcat (screen_data.screen, screen_data.str9);
                        correct_guesses_to_str (&tux, screen_data.screen);
                        failed_guesses_to_str (&tux, screen_data.screen);

                        do
                            {
                                clear ();
                                print_game_scr (&tux, screen_data.screen, RED_FOR_LOSS_SCREEN, &tux.set_color);
                                print_str_between_two_colors (GREEN_PAIR, WHITE_PAIR, "\n   Return to menu? (Y/n): ", &tux.set_color);
                                getstr (tux.input);

                                check_response (&tux, TRUE);
                            }
                        while ( (tux.play != FALSE) && (tux.play != TRUE));
                        tux.option = WELCOME_SCREEN;
                    }
                    else if (tux.option == GAME_SCREEN)
                    {
                        do
                            {
                                clear ();
                                print_game_scr (&tux, screen_data.screen, tux.color_option, &tux.set_color);
                                print_str_between_two_colors (GREEN_PAIR, WHITE_PAIR, "\n   Press 'y' to get new word: ", &tux.set_color);
                                getstr (tux.input);

                                check_response (&tux, FALSE);
                            }
                        while ( (tux.play != FALSE) && (tux.play != TRUE));
                        tux.option = GAME_SCREEN;
                    }
                    break;
                case ABOUT_SCREEN:
                    do
                        {
                            clear ();
                            print_str (screen_data.str10, BROWN_FOR_MENU_SCREENS, &tux.set_color);
                            print_str_between_two_colors (GREEN_PAIR, WHITE_PAIR, "\n   Press 'y' to return to menu: ", &tux.set_color);
                            getstr (tux.input);

                            check_response (&tux, FALSE);
                        }
                    while( (tux.play != FALSE) && (tux.play != TRUE));
                    tux.option = WELCOME_SCREEN;
                    break;
                case QUIT_GAME:
                    tux.play = FALSE;
                    break;
                case RETURN_TO_MENU_PROMPT:
                    do
                        {
                            print_game_scr (&tux, screen_data.screen, BLUE_FOR_PENGUIN, &tux.set_color);
                            print_str_between_two_colors (GREEN_PAIR, WHITE_PAIR, "\n   Return to menu? (Y/n): ", &tux.set_color);
                            getstr (tux.input);

                            check_response (&tux, TRUE);
                        }
                    while ( (tux.play != FALSE) && (tux.play != TRUE));
                    tux.option = WELCOME_SCREEN;
            }
        }
    }
    else
    {
        set_color_if_possible (RED_PAIR, &tux.set_color);
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






void check_response (Penguin *tux, const int no_option)
{
    if (strlen(tux->input) < INPUT_SIZE)
    {
        if ( (tux->input[0] == 'y') || (tux->input[0] == 'Y'))
        {
            tux->play = TRUE;
        }
        else if ( ((tux->input[0] == 'n') || (tux->input[0] == 'N')) && (no_option == TRUE))
        {
            tux->play = FALSE;
        }
        else
        {
            tux->play = NOT_FALSE_OR_TRUE;
        }
    }
    else
    {
        tux->play = NOT_FALSE_OR_TRUE;
    }
}
