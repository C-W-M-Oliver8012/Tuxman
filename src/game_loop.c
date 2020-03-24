#include "../include/game_loop.h"
#include "../include/menu_system.h"
#include "../include/functions.h"


void set_category (Penguin *tux, Game_States *screen_data, Game_Options *game_info, Categories *categories)
{
    if ((tux->option == GAME_SCREEN) && (tux->category_has_been_set == FALSE))
    {
        do
            {
                tux->category_choice = -1;

                clear ();
                print_str (screen_data->str12, BROWN_FOR_MENU_SCREENS, &game_info->set_color);
                set_color_if_possible (WHITE_PAIR, &game_info->set_color);

                for (int i = 0; i < categories->category_count; i++)
                {
                    print_str_between_two_colors (BROWN_PAIR, WHITE_PAIR, "   |", &game_info->set_color);
                    printw (" %2d) %-15s - %-30s", i+1, categories->filename[i], categories->description[i]);
                    set_color_if_possible (BROWN_PAIR, &game_info->set_color);
                    printw (" |\n");
                }

                print_str_between_two_colors (BROWN_PAIR, GREEN_PAIR, "   ========================================================\n", &game_info->set_color);
                printw ("\n   Category option: ");
                set_color_if_possible (WHITE_PAIR, &game_info->set_color);
                getstr (tux->input);
                
                if (strlen (tux->input) < 4)
                {
                    if (str_is_int (tux->input) == TRUE)
                    {
                        tux->category_choice = strtol (tux->input, NULL, 10);
                    }
                }
                else
                {
                    tux->category_choice = -1;
                }

                tux->category_choice--;
            }
        while((tux->category_choice < 0) || (tux->category_choice > 24) || (tux->category_choice >= categories->category_count));

        tux->category_has_been_set = TRUE;
    }
}



void reset_game (Penguin *tux, Game_States *screen_data, Game_Options *game_info, Categories *categories)
{
    strcpy (screen_data->screen, "");
    if (tux->option == GAME_SCREEN)
    {
        game_info->pickLine = rand () % categories->word_count[tux->category_choice];
        strcpy (tux->word, tux->words[tux->category_choice][game_info->pickLine]);
        strtok (tux->word, "\n");
        tux->wordLength = strlen (tux->word);
        tux->indexLength = 0;
        tux->letters_guessed = 0;
        strcpy (tux->input, "");
        tux->choice = ' ';
        tux->fails = 0;
        tux->win = FALSE;
    }
}



void game_loop (Penguin *tux, Game_States *screen_data, Game_Options *game_info)
{
    while ( (tux->option == GAME_SCREEN) && (tux->fails != 7) && (tux->win == FALSE))            // game loop
    {
        clear ();
        strcpy (screen_data->screen, "");
        if (tux->fails == 6)                          // PLAYER LOST AND THEREFOR LOSES A LIFE
        {
            tux->lives--;
        }

        get_screen_by_fails (screen_data, &tux->fails, &game_info->color_option);

        correct_guesses_to_str (tux, screen_data->screen);
        failed_guesses_to_str (tux, screen_data->screen);

        if ( (tux->fails != 7) && (tux->win == FALSE))      // HASN'T LOST YET & HASN'T WON YET
        {
            if (tux->choice == '@')                   // GUESS ENTIRE WORD
            {
                guess_entire_word (tux, screen_data->screen, &game_info->set_color);
            }
            else                                    // NORMAL TURN
            {
                guess_single_char (tux, screen_data->screen, &game_info->set_color);
                check_exit_game (&tux->choice, &tux->fails, &tux->option);
            }

            if (tux->win == TRUE)                        // PLAYER WINS
            {
                set_win (tux, screen_data, &game_info->color_option);
            }
        }
    }
}



void get_screen_by_fails (Game_States *screen_data, long unsigned int *fails, int *color_option)
{
    switch (*fails)                          // GETS PROPER GRAPHIC TO PRINT
    {

        case 0:
            strcat (screen_data->screen, screen_data->str1);
            break;
        case 1:
            strcat (screen_data->screen, screen_data->str2);
            break;
        case 2:
            strcat (screen_data->screen, screen_data->str3);
            break;
        case 3:
            strcat (screen_data->screen, screen_data->str4);
            break;
        case 4:
            strcat (screen_data->screen, screen_data->str5);
            break;
        case 5:
            strcat (screen_data->screen, screen_data->str6);
            break;
        case 6:
            strcat (screen_data->screen, screen_data->str7);
            *fails = 7;
            *color_option = 4;
            break;
    }
}



void guess_entire_word (Penguin *tux, const char *screen, const int *set_color)
{
    print_game_scr (&tux->score, &tux->lives, screen, BLUE_FOR_PENGUIN, set_color);
    print_str_between_two_colors (GREEN_PAIR, WHITE_PAIR, "\n   Guess the word: ", set_color);
    getstr (tux->input);

    tux->win = check_full_guess (tux);
    if (tux->win == FALSE)                    // wrong guess
    {
        tux->failedGuesses[tux->fails] = '@';
        tux->fails = tux->fails + 1;
        tux->choice = '^';
        strcpy (tux->input, "");
    }
    else                                // you win and all letters in word are added to index
    {
        for (int i = 0; i < tux->wordLength; i++)
        {
            int matched = 0;

            for (int j = 0; j < tux->indexLength; j++)
            {
                if ( (tux->word[i] == tux->index[j]) || (tux->word[i] == ' '))
                {
                    matched = 1;
                }
            }

            if (matched == 0)
            {
                tux->index[tux->indexLength] = tux->word[i];
                tux->indexLength++;
            }
        }
    }
}



void guess_single_char (Penguin *tux, const char *screen, const int *set_color)
{
    print_game_scr (&tux->score, &tux->lives, screen, BLUE_FOR_PENGUIN, set_color);
    print_str_between_two_colors (GREEN_PAIR, WHITE_PAIR, "\n   Pick a letter: ", set_color);
    getstr (tux->input);

    if (strlen (tux->input) < INPUT_SIZE)
    {
        tux->choice = tux->input[0];
        int valid;
        if (check_guess_is_valid (tux) == 0)
        {
            valid = check_guess (tux);
        }
        else
        {
            valid = 3;
        }
        if (valid == 0)
        {
            tux->failedGuesses[tux->fails] = tux->choice;
            tux->fails++;
        }
        else if (valid == 1)
        {
            tux->index[tux->indexLength] = tux->choice;
            tux->indexLength++;
        }

        tux->win = has_won (tux);
    }
}



void check_exit_game (const char *choice, long unsigned int *fails, long unsigned int *option)
{
    if (*choice == '^')                // ENDS GAME
    {
        *fails = 7;
        *option = RETURN_TO_MENU_PROMPT;
    }
}



void set_win (Penguin *tux, Game_States *screen_data, int *color_option)
{
    strcpy (screen_data->screen, "");
    int add = add_score (tux);
    tux->score = tux->score + add;
    int diff = tux->score - tux->max_score;
    while (diff >= 10)
    {
        tux->lives++;
        tux->max_score = tux->max_score + 10;
        diff = tux->score - tux->max_score;
    }
    if (tux->score >= tux->max_score)
    {
        tux->lives++;
        tux->max_score = tux->max_score + 10;
    }
    strcat (screen_data->screen, screen_data->str8);
    correct_guesses_to_str (tux, screen_data->screen);
    failed_guesses_to_str (tux, screen_data->screen);
    *color_option = 3;
}
