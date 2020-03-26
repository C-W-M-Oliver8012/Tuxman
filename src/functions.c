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


void file_to_str (const char *filename, char *file_data, int *did_open)
{
    FILE *file;

    char buff[SIZE];

    char dir[NAME_SIZE];
    strcpy (dir, DIR);
    strcat (dir, filename);

    file = fopen (dir, "r");

    strcpy (file_data, "");

    if (file != NULL)
    {
        while (fgets (buff, SIZE, (FILE*)file))
        {
            strcat (file_data, buff);
        }

        fclose (file);
    }
    else
    {
        *did_open = FALSE;
    }
}



int get_file_length (const char *filename, int *did_open)
{
    FILE *file;

    char dir[NAME_SIZE];
    strcpy (dir, DIR);
    strcat (dir, filename);

    file = fopen (dir, "r");

    char buff[SIZE];
    int wordCount = 0;

    if (file != NULL)
    {
        while (fgets (buff, SIZE, (FILE*)file))
        {
            wordCount++;
        }

        fclose (file);
    }
    else
    {
        *did_open = FALSE;
    }

    return wordCount;
}



void get_categories_filename_description (Categories *categories, int *did_open)
{
    FILE *file;

    char dir[NAME_SIZE];
    strcpy (dir, DIR);
    strcat (dir, "data/categories.txt");

    file = fopen (dir, "r");

    char buff[SIZE];

    if (file != NULL)
    {
        int i = 0;
        char *token;
        while ((fgets (buff, SIZE, (FILE*)file)) && (i < categories->category_count))
        {
            token = strtok (buff, "-");
            strcpy (categories->filename[i], token);
            token = strtok (NULL, "-");
            strcpy (categories->description[i], token);
            i++;
        }

        fclose (file);
    }
    else
    {
        *did_open = FALSE;
    }
}



void get_words (const char *filename, char **words, int *wordCount, int *did_open)
{
    FILE *file;

    char dir[NAME_SIZE];
    strcpy (dir, DIR);
    strcat (dir, filename);

    file = fopen (dir, "r");

    char buff[SIZE];

    if (file != NULL)
    {
        int i = 0;
        while (fgets (buff, SIZE, (FILE*)file) && (i < *wordCount))
        {
            strcpy (words[i], buff);
            i++;
        }

        fclose (file);
    }
    else
    {
        *did_open = FALSE;
    }
}



int str_is_int (const char *str)
{
    int length = strlen (str);
    int match = TRUE;

    for (int i = 0; i < length; i++)
    {
        switch (str[i])
        {
            case '1':
                break;
            case '2':
                break;
            case '3':
                break;
            case '4':
                break;
            case '5':
                break;
            case '6':
                break;
            case '7':
                break;
            case '8':
                break;
            case '9':
                break;
            case '0':
                break;
            default:
                match = FALSE;
        }
    }

    return match;
}



void correct_guesses_to_str (const Penguin *tux, char *screen)
{
    strcat (screen, "\n\n   ");
    char formated_letters[SIZE];

    for (int i = 0; i < tux->wordLength; i++)
    {
        int matched = 0;

        if ( ( (tux->fails == 6) && (tux->word[i] != ' ')) || (tux->win == 1))
        {
            strcpy (formated_letters, "");
            formated_letters[0] = tux->word[i];
            formated_letters[1] = ' ';
            formated_letters[2] = '\0';
            strcat (screen, formated_letters);
            matched++;
        }
        else if ( ( (tux->fails == 6) && (tux->word[i] == ' ')) || (tux->win == 1))
        {
            strcat (screen, "  ");
            matched++;
        }

        if (tux->fails != 6 && tux->indexLength != 0 && (tux->word[i] != ' ') && (tux->win != 1))
        {
            for (int j = 0; j < tux->indexLength; j++)
            {
                if (tux->word[i] == tux->index[j])
                {
                    strcpy (formated_letters, "");
                    formated_letters[0] = tux->word[i];
                    formated_letters[1] = ' ';
                    formated_letters[2] = '\0';
                    strcat (screen, formated_letters);
                    matched++;
                    break;
                }
            }
            if (matched == 0)
            {
                strcat (screen, "  ");
            }
        }
        else if ( (tux->word[i] == ' ') && (tux->fails != 6) && (tux->win != 1))
        {
            strcat (screen, "  ");
        }
    }

    strcat (screen, "\n   ");
    for (int i = 0; i < tux->wordLength; i++)
    {
        if (tux->word[i] != ' ')
        {
            strcat (screen, "- ");
        }
        else
        {
            strcat (screen, "  ");
        }
    }
}



void failed_guesses_to_str (const Penguin *tux, char *screen)
{
    char formated_letters[SIZE];

    strcat (screen, "\n\n\n   Bad guesses: ");
    for (int i = 0; i < tux->fails; i++)
    {
        strcpy (formated_letters, "");
        formated_letters[0] = tux->failedGuesses[i];
        formated_letters[1] = ' ';
        formated_letters[2] = '\0';
        strcat (screen, formated_letters);
    }
}



int check_guess_is_valid (const Penguin *tux)
{
    int matched = TRUE;

    if ( (tux->choice == '\0') || (tux->choice == ' ') || (tux->choice == '@') || (tux->choice == '^') || (strlen(tux->input) > INPUT_SIZE) || (tux->choice == '\n'))
    {
        matched = FALSE;
    }

    for (int i = 0; i < tux->indexLength; i++)
    {
        if (tux->choice == tux->index[i])
        {
            matched = FALSE;
        }
    }

    for (int i = 0; i < tux->fails; i++)
    {
        if (tux->choice == tux->failedGuesses[i])
        {
            matched = FALSE;
        }
    }

    return matched;
}



int check_guess (const Penguin *tux)
{
    int matched = FALSE;

    for (int i = 0; i <= tux->indexLength; i++)
    {
        for (int j = 0; j < tux->wordLength; j++)
        {
            if (tux->choice == tux->word[j])
            {
                return TRUE;
            }
        }
    }

    return matched;
}



int has_won (const Penguin *tux)
{
    int letters_guessed = 0;

    for (int i = 0; i < tux->wordLength; i++)
    {
        for (int j = 0; j < tux->indexLength; j++)
        {
            if ( (tux->word[i] == tux->index[j]) && (tux->word[i] != ' '))
            {
                letters_guessed++;
            }
        }
        if (tux->word[i] == ' ')
        {
            letters_guessed++;
        }
    }

    if (tux->win == TRUE)
    {
        return TRUE;
    }

    if (letters_guessed == tux->wordLength)
    {
        return TRUE;
    }

    return NOT_FALSE_OR_TRUE;
}



int check_full_guess (const Penguin *tux)
{
    if (strcmp (tux->word, tux->input) == 0)
    {
        return TRUE;
    }

    return NOT_FALSE_OR_TRUE;
}



int add_score (const Penguin *tux)
{
    switch (tux->fails)
    {
        case 5:
            return 1 + tux->indexLength;
        case 4:
            return 2 + tux->indexLength;
        case 3:
            return 3 + tux->indexLength;
        case 2:
            return 4 + tux->indexLength;
        case 1:
            return 5 + tux->indexLength;
        case 0:
            return 6 + tux->indexLength;
    }

    return 0;
}



void print_str (const char *str, const int color, const int *set_color)
{
    int length = strlen (str);
    int x = 0;
    int y = 0;

    for (int i = 0; i < length; i++)
    {
        if (*set_color == TRUE)
        {
            if ((color == 1) || (color == 3) || (color == 4))
            {
                if (str[i] == '\n')
                {
                    y++;
                    x = 0;
                }
                else
                {
                    x++;
                }

                if ( (y > 2) && (y < 14) && (x > 3) && (x < 30) && (color == BLUE_FOR_PENGUIN))                        // penguin
                {
                    attron (COLOR_PAIR (BLUE_PAIR));
                }
                else if ( (y > 2) && (y < 14) && (x > 3) && (x < 30) && (color == GREEN_FOR_WIN_SCREEN))                   // green for win
                {
                    attron (COLOR_PAIR (GREEN_PAIR));
                }
                else if ( (y > 2) && (y < 14) && (x > 3) && (x < 30) && (color == RED_FOR_LOSS_SCREEN))                   // red for lose
                {
                    attron (COLOR_PAIR (RED_PAIR));
                }
                else if ( (y == 22) && (x < 17))                                                        // red for bad guesses
                {
                    attron (COLOR_PAIR (RED_PAIR));
                }
                else if (y < 17)                                                                        // brown for everything else
                {
                    attron (COLOR_PAIR (BROWN_PAIR));
                }
                else
                {
                    attron (COLOR_PAIR (WHITE_PAIR));
                }

                if ( (y > 4) && (y < 7) && (x > 10) && (x < 14))                                        // yellow for beak
                {
                    attron (COLOR_PAIR (YELLOW_PAIR));
                }
                if ( ((y == 11) && (x > 6) && (x < 9)) || ((y == 11) && (x > 15) && (x < 18)))        // yellow for top of feet
                {
                    attron (COLOR_PAIR (YELLOW_PAIR));
                }
                if ( (y == 12) && (x > 6) && (x < 18))                                                 // yellow for bottom of feet
                {
                    attron (COLOR_PAIR (YELLOW_PAIR));
                }
                if ((str[i] == 'o') && (y < 17))                                                        // white for the eyes
                {
                    attron (COLOR_PAIR (WHITE_PAIR));
                }
            }
            else if (color == BROWN_FOR_MENU_SCREENS)
            {
                if ((str[i] == '=') || (str[i] == '|'))
                {
                    attron (COLOR_PAIR (BROWN_PAIR));
                }
                else
                {
                    attron (COLOR_PAIR (WHITE_PAIR));
                }
            }
        }

        addch (str[i]);
    }

    set_color_if_possible (WHITE_PAIR, set_color);
}



void print_game_scr (const Penguin *tux, const char *screen, const int color_option, const int *set_color)
{
    clear ();
    print_str_between_two_colors (GREEN_PAIR, WHITE_PAIR, "\n   Score: ", set_color);
    printw ("%d", tux->score);
    print_str_between_two_colors (RED_PAIR, WHITE_PAIR, "               Lives: ", set_color);
    printw ("%d\n", tux->lives);
    print_str (screen, color_option, set_color);
}



void set_color_if_possible (const int color, const int *set_color)
{
    if (*set_color == TRUE)
    {
        attron (COLOR_PAIR (color));
    }
}



void print_str_between_two_colors (const int first_color, const int second_color, const char *str, const int *set_color)
{
    if (*set_color == TRUE)
    {
        attron (COLOR_PAIR (first_color));
    }
    printw ("%s", str);
    if (*set_color == TRUE)
    {
        attron (COLOR_PAIR (second_color));
    }
}
