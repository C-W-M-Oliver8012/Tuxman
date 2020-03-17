#include "../headers/functions.h"

void file_to_str (char *filename, char *file_data)
{
    FILE *file;

    char buff[SIZE];

    file = fopen (filename, "a+");

    while (fgets (buff, SIZE, (FILE*)file))
    {
        strcat (file_data, buff);
    }
    strcat (file_data, "\n");

    fclose (file);
}

void get_word (char *word)
{
    FILE *file;

    file = fopen ("data/words.txt", "a+");

    int wordCount = 0;
    while (fgets(word, SIZE, (FILE*)file))
    {
        wordCount++;
    }

    time_t t;
    srand ( (unsigned) time (&t));
    int pickLine = rand () % wordCount + 1;

    wordCount = 1;
    file = fopen ("data/words.txt", "a+");
    while (fgets (word, SIZE, (FILE*)file) && wordCount < pickLine)
    {
        wordCount++;
    }

    fclose (file);
}

void correct_guesses_to_str (struct Penguin *tux, char *guess_data)
{
    strcat (guess_data, "   ");
    char formated_letters[SIZE];

    for (int i = 0; i < tux->wordLength; i++)
    {
        int matched = 0;

        if ( ( (tux->fails == 7) && (tux->word[i] != ' ')) || (tux->win == 1))
        {
            strcpy (formated_letters, "");
            formated_letters[0] = tux->word[i];
            formated_letters[1] = ' ';
            formated_letters[2] = '\0';
            strcat (guess_data, formated_letters);
            matched++;
        }
        else if ( ( (tux->fails == 7) && (tux->word[i] == ' ')) || (tux->win == 1))
        {
            strcat (guess_data, "  ");
            matched++;
        }

        if (tux->fails != 7 && tux->indexLength != 0 && (tux->word[i] != ' ') && (tux->win != 1))
        {
            for (int j = 0; j < tux->indexLength; j++)
            {
                if (tux->word[i] == tux->index[j])
                {
                    strcpy (formated_letters, "");
                    formated_letters[0] = tux->word[i];
                    formated_letters[1] = ' ';
                    formated_letters[2] = '\0';
                    strcat (guess_data, formated_letters);
                    matched++;
                    break;
                }
            }
            if (matched == 0)
            {
                strcat (guess_data, "  ");
            }
        }
        else if ( (tux->word[i] == ' ') && (tux->fails != 7) && (tux->win != 1))
        {
            strcat (guess_data, "  ");
        }
    }

    strcat (guess_data, "\n   ");
    for (int i = 0; i < tux->wordLength; i++)
    {
        if (tux->word[i] != ' ')
        {
            strcat (guess_data, "- ");
        }
        else
        {
            strcat (guess_data, "  ");
        }
    }
}

// PRINTS FAILED GUESSES
void failed_guesses_to_str (struct Penguin *tux, char *guess_data)
{
    char formated_letters[SIZE];

    strcat (guess_data, "\n\n   Bad guesses: ");
    for (int i = 0; i < tux->fails; i++)
    {
        strcpy (formated_letters, "");
        formated_letters[0] = tux->failedGuesses[i];
        formated_letters[1] = ' ';
        formated_letters[2] = '\0';
        strcat (guess_data, formated_letters);
    }
}

int check_guess_is_valid (struct Penguin *tux)
{
    int matched = 0;

    if ( (tux->choice == '\0') || (tux->choice == ' ') || (tux->choice == '@') || (tux->choice == '^') || (strlen(tux->s_choice) > INPUT_SIZE) || (tux->choice == '\n'))
    {
        matched = 1;
    }

    for (int i = 0; i < tux->indexLength; i++)
    {
        if (tux->choice == tux->index[i])
        {
            matched = 1;
        }
    }

    for (int i = 0; i < tux->fails; i++)
    {
        if (tux->choice == tux->failedGuesses[i])
        {
            matched = 1;
        }
    }

    return matched;
}

int check_guess (struct Penguin *tux)
{
    int matched = 0;

    for (int i = 0; i <= tux->indexLength; i++)
    {
        for (int j = 0; j < tux->wordLength; j++)
        {
            if (tux->choice == tux->word[j])
            {
                matched = 1;
                return matched;
            }
        }
    }

    return matched;
}

int has_won (struct Penguin *tux)
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

    if (tux->win == 1)
    {
        return 1;
    }

    if (letters_guessed == tux->wordLength)
    {
        return 1;
    }

    return 0;
}

int check_full_guess (struct Penguin *tux)
{
    if (strcmp (tux->word, tux->s_choice) == 0)
    {
        return 1;
    }

    return 0;
}

int add_score (struct Penguin *tux)
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

void print_str (char *str, int color)
{
    int length = strlen (str);
    int x = 0;
    int y = 0;

    for (int i = 0; i < length; i++)
    {
        if (color == 1)
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

            if ( (y > 2) && (y < 14) && (x > 7) && (x < 40))
            {
                attron (COLOR_PAIR (3));
            }
            else if (y > 16)
            {
                attron (COLOR_PAIR (5));
            }
            else
            {
                attron (COLOR_PAIR (6));
            }

            if ( (y > 4) && (y < 7) && (x > 14) && (x < 18))
            {
                attron (COLOR_PAIR (4));
            }
            if ( ((y == 11) && (x > 10) && (x < 13)) || ((y == 11) && (x > 19) && (x < 22)))
            {
                attron (COLOR_PAIR (4));
            }
            if ( (y == 12) && (x > 10) && (x < 22))
            {
                attron (COLOR_PAIR (4));
            }
            if ((str[i] == 'o') && (y < 17))
            {
                attron (COLOR_PAIR (5));
            }
            if ( (y == 21) && (x < 16))
            {
                attron (COLOR_PAIR (2));
            }
            else if ( (y == 21) && (x > 17))
            {
                attron (COLOR_PAIR (5));
            }
            else if (y == 22)
            {
                attron (COLOR_PAIR (1));
            }
        }
        else if (color == 2)
        {
            if ((str[i] == '=') || (str[i] == '|'))
            {
                attron (COLOR_PAIR (6));
            }
            else
            {
                attron (COLOR_PAIR (5));
            }
        }
        addch (str[i]);
    }
}
