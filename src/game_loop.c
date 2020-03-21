#include "../include/game_loop.h"
#include "../include/menu_system.h"

void reset_game (struct Penguin *tux, struct Game_States *screen_data, struct Game_Options *game_info)
{
    strcpy (screen_data->screen, "");
    if (tux->option == GAME_SCREEN)
    {
        game_info->pickLine = rand () % game_info->wordCount;
        strcpy (tux->word, tux->words[game_info->pickLine]);
        strtok (tux->word, "\n");
        tux->wordLength = strlen (tux->word);
        tux->indexLength = 0;
        tux->letters_guessed = 0;
        strcpy (tux->s_choice, "");
        tux->choice = ' ';
        tux->fails = 0;
        tux->win = FALSE;
    }
}

void game_loop (struct Penguin *tux, struct Game_States *screen_data, struct Game_Options *game_info)
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
                guess_entire_word (tux, screen_data->screen, &game_info->color_option, game_info->tux_win);
            }
            else                                    // NORMAL TURN
            {
                guess_single_char (tux, screen_data->screen, &game_info->color_option, game_info->tux_win);
                check_exit_game (&tux->choice, &tux->fails, &tux->option);
            }

            if (tux->win == TRUE)                        // PLAYER WINS
            {
                set_win (tux, screen_data, &game_info->color_option);
            }
        }
    }
}

void get_screen_by_fails (struct Game_States *screen_data, long unsigned int *fails, int *color_option)
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

void guess_entire_word (struct Penguin *tux, const char *screen, int *color_option, WINDOW *tux_win)
{
    *color_option = 1;
    print_game_scr (&tux->score, &tux->lives, screen, color_option);
    attron (COLOR_PAIR (GREEN_PAIR));
    printw ("\n   Guess the word: ");
    attron (COLOR_PAIR (WHITE_PAIR));
    getstr (tux->s_choice);
    wrefresh (tux_win);

    tux->win = check_full_guess (tux);
    if (tux->win == FALSE)                    // wrong guess
    {
        tux->failedGuesses[tux->fails] = '@';
        tux->fails = tux->fails + 1;
        tux->choice = '^';
        strcpy (tux->s_choice, "");
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

void guess_single_char (struct Penguin *tux, const char *screen, int *color_option, WINDOW *tux_win)
{
    *color_option = 1;
    print_game_scr (&tux->score, &tux->lives, screen, color_option);
    attron (COLOR_PAIR (GREEN_PAIR));
    printw ("\n   Pick a letter: ");
    attron (COLOR_PAIR (WHITE_PAIR));
    getstr (tux->s_choice);
    wrefresh (tux_win);

    if (strlen (tux->s_choice) < INPUT_SIZE)
    {
        tux->choice = tux->s_choice[0];
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

void set_win (struct Penguin *tux, struct Game_States *screen_data, int *color_option)
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
