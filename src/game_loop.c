#include "../headers/game_loop.h"
#include "../headers/menu_system.h"

void game_loop (struct Penguin *tux, char *file_data, char *str1, char *str2, char *str3, char *str4, char *str5, char *str6, char *str7, char *str8, WINDOW *tux_win, int *color_option)
{
    while ( (tux->option == '1') && (tux->fails != 7) && (tux->win == 0))            // game loop
    {
        clear ();
        strcpy (file_data, "");
        if (tux->fails == 6)                          // PLAYER LOST AND THEREFOR LOSES A LIFE
        {
            tux->lives--;
        }

        switch (tux->fails)                          // GETS PROPER GRAPHIC TO PRINT
        {
            case 0:
                strcat (file_data, str1);
                break;
            case 1:
                strcat (file_data, str2);
                break;
            case 2:
                strcat (file_data, str3);
                break;
            case 3:
                strcat (file_data, str4);
                break;
            case 4:
                strcat (file_data, str5);
                break;
            case 5:
                strcat (file_data, str6);
                break;
            case 6:
                strcat (file_data, str7);
                tux->fails = 7;
                *color_option = 4;
                break;
        }

        correct_guesses_to_str (tux, file_data);
        failed_guesses_to_str (tux, file_data);

        if ( (tux->fails != 7) && (tux->win == 0))      // HASN'T LOST YET & HASN'T WON YET
        {
            if (tux->choice == '@')                   // GUESS ENTIRE WORD
            {
                *color_option = 1;
                print_game_scr (&tux->score, &tux->lives, file_data, &*color_option);
                attron (COLOR_PAIR (1));
                printw ("\n   Guess the word: ");
                attron (COLOR_PAIR (5));
                getstr (tux->s_choice);
                wrefresh (tux_win);

                tux->win = check_full_guess (tux);
                if (tux->win == 0)                    // wrong guess
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
            else                                    // NORMAL TURN
            {
                *color_option = 1;
                print_game_scr (&tux->score, &tux->lives, file_data, &*color_option);
                attron (COLOR_PAIR (1));
                printw ("\n   Pick a letter: ");
                attron (COLOR_PAIR (5));
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

                if (tux->choice == '^')                // ENDS GAME
                {
                    tux->fails = 7;
                    tux->option = '4';
                }
            }

            if (tux->win == 1)                        // PLAYER WINS
            {
                strcpy (file_data, "");
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
                strcat (file_data, str8);
                correct_guesses_to_str (tux, file_data);
                failed_guesses_to_str (tux, file_data);
                *color_option = 3;
            }
        }
    }
}
