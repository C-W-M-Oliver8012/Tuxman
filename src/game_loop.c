#include "../include/game_loop.h"
#include "../include/menu_system.h"
#include "../include/functions.h"


void set_category (Penguin *tux, const Game_States *screen_data, Game_Options *game_info, Categories *categories)
{
    if (tux->category_has_been_set == FALSE)
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
    game_info->pickLine = rand () % categories->word_count[tux->category_choice];
    strcpy (tux->word, tux->words[tux->category_choice][game_info->pickLine]);
    strtok (tux->word, "\n");
    tux->wordLength = strlen (tux->word);
    tux->indexLength = 0;
    tux->letters_guessed = 0;
    tux->choice = ' ';
    tux->fails = 0;
    tux->win = NOT_FALSE_OR_TRUE;
}



void game_loop (Penguin *tux, Game_States *screen_data, Game_Options *game_info)
{
    while (tux->win == NOT_FALSE_OR_TRUE)
    {
        clear ();
        strcpy (screen_data->screen, "");

        get_screen_by_fails (screen_data, &tux->fails, &game_info->color_option);

        correct_guesses_to_str (tux, screen_data->screen);
        failed_guesses_to_str (tux, screen_data->screen);

        if (tux->win == NOT_FALSE_OR_TRUE)
        {
            print_game_scr (tux, screen_data->screen, BLUE_FOR_PENGUIN, &game_info->set_color);

            if (tux->choice == '@')
            {
                guess_entire_word (tux, &game_info->set_color);
                check_if_player_has_lost (&tux->fails, &tux->win, &tux->option);
            }
            else
            {
                guess_single_char (tux, &game_info->set_color);
                check_if_player_has_lost (&tux->fails, &tux->win, &tux->option);
                check_exit_game (&tux->choice, &tux->win, &tux->option);
            }
        }

        if ((tux->win == FALSE) && (tux->option == GAME_SCREEN))
        {
            strcpy (screen_data->screen, "");
            strcat (screen_data->screen, screen_data->str7);
            correct_guesses_to_str (tux, screen_data->screen);
            failed_guesses_to_str (tux, screen_data->screen);
            game_info->color_option = 4;
            tux->lives--;
        }

        if (tux->win == TRUE)
        {
            set_win (tux, screen_data, &game_info->color_option);
        }
    }
}



void get_screen_by_fails (Game_States *screen_data, int *fails, int *color_option)
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
    }
}



void guess_entire_word (Penguin *tux, const int *set_color)
{
    print_str_between_two_colors (GREEN_PAIR, WHITE_PAIR, "\n   Guess the word: ", set_color);
    getstr (tux->input);

    tux->win = check_full_guess (tux);
    if (tux->win == NOT_FALSE_OR_TRUE)
    {
        tux->failedGuesses[tux->fails] = '@';
        tux->fails = tux->fails + 1;
        tux->choice = ' ';
    }
    else if (tux->win == TRUE)
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



void guess_single_char (Penguin *tux, const int *set_color)
{
    print_str_between_two_colors (GREEN_PAIR, WHITE_PAIR, "\n   Pick a letter: ", set_color);
    getstr (tux->input);

    if (strlen (tux->input) < INPUT_SIZE)
    {
        tux->choice = tux->input[0];
        int valid;
        if (check_guess_is_valid (tux) == TRUE)
        {
            valid = check_guess (tux);
        }
        else
        {
            valid = NOT_FALSE_OR_TRUE;
        }
        if (valid == FALSE)
        {
            tux->failedGuesses[tux->fails] = tux->choice;
            tux->fails++;
        }
        else if (valid == TRUE)
        {
            tux->index[tux->indexLength] = tux->choice;
            tux->indexLength++;
        }

        tux->win = has_won (tux);
    }
}



void check_if_player_has_lost (int *fails, int *win, int *option)
{
    if (*fails == 6)
    {
        *win = FALSE;
        *option = GAME_SCREEN;
    }
}



void check_exit_game (const char *choice, int *win, int *option)
{
    if (*choice == '^')
    {
        *win = FALSE;
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
