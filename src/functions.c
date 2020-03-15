#include "../headers/functions.h"

void get_file_data(char *filename, char *file_data)
{
    FILE *file;

    char buff[SIZE];

    file = fopen(filename, "a+");

    while(fgets(buff, SIZE, (FILE*)file))
    {
        strcat(file_data, buff);
    }
    strcat(file_data, "\n");

    fclose(file);
}

void get_word(char *word)
{
    FILE *file;

    file = fopen("data/words.txt", "a+");

    int wordCount = 0;
    while(fgets(word, SIZE, (FILE*)file))
    {
        wordCount++;
    }

    time_t t;
    srand((unsigned) time(&t));
    int pickLine = rand() % wordCount + 1;

    wordCount = 1;
    file = fopen("data/words.txt", "a+");
    while(fgets(word, SIZE, (FILE*)file) && wordCount < pickLine)
    {
        wordCount++;
    }

    fclose(file);
}

void correct_guesses_to_str(struct Penguin *tux, char *guess_data)
{
    strcat(guess_data, "   ");
    char formated_letters[SIZE];

    for(int i = 0; i < tux->wordLength; i++)
    {
        int matched = 0;

        if(((tux->fails == 7) && (tux->word[i] != ' ')) || (tux->win == 1))
        {
            strcpy(formated_letters, "");
            formated_letters[0] = tux->word[i];
            formated_letters[1] = ' ';
            formated_letters[2] = '\0';
            strcat(guess_data, formated_letters);
            matched++;
        }
        else if(((tux->fails == 7) && (tux->word[i] == ' ')) || (tux->win == 1))
        {
            strcat(guess_data, "  ");
            matched++;
        }

        if(tux->fails != 7 && tux->indexLength != 0 && (tux->word[i] != ' ') && (tux->win != 1))
        {
            for(int j = 0; j < tux->indexLength; j++)
            {
                if(tux->word[i] == tux->index[j])
                {
                    strcpy(formated_letters, "");
                    formated_letters[0] = tux->word[i];
                    formated_letters[1] = ' ';
                    formated_letters[2] = '\0';
                    strcat(guess_data, formated_letters);
                    matched++;
                    break;
                }
            }
            if(matched == 0)
            {
                strcat(guess_data, "  ");
            }
        }
        else if((tux->word[i] == ' ') && (tux->fails != 7) && (tux->win != 1))
        {
            strcat(guess_data, "  ");
        }
    }

    strcat(guess_data, "\n   ");
    for(int i = 0; i < tux->wordLength; i++)
    {
        if(tux->word[i] != ' ')
        {
            strcat(guess_data, "- ");
        }
        else
        {
            strcat(guess_data, "  ");
        }
    }
}

// PRINTS FAILED GUESSES
void failed_guesses_to_str(struct Penguin *tux, char *guess_data)
{
    char formated_letters[SIZE];

    strcat(guess_data, "\n\n   Bad guesses: ");
    for(int i = 0; i < tux->fails; i++)
    {
        strcpy(formated_letters, "");
        formated_letters[0] = tux->failedGuesses[i];
        formated_letters[1] = ' ';
        formated_letters[2] = '\0';
        strcat(guess_data, formated_letters);
    }
}

int check_guess(struct Penguin *tux)
{
    int matched = 0;
    int checkIndex = 0;

    if((tux->choice == '\0') || (tux->choice == ' ') || (tux->choice == '@') || (tux->choice == '^') || (strlen(tux->s_choice) > INPUT_SIZE) || (tux->choice == '\n'))
    {
        checkIndex = 1;
        matched = 3;
    }

    for(int i = 0; i < tux->indexLength; i++)
    {
        if(tux->choice == tux->index[i])
        {
            checkIndex = 1;
            matched = 3;
        }
    }

    for(int i = 0; i < tux->fails; i++)
    {
        if(tux->choice == tux->failedGuesses[i])
        {
            checkIndex = 1;
            matched = 3;
        }
    }

    if(checkIndex != 1)
    {
        for(int i = 0; i <= tux->indexLength; i++)
        {
            for(int j = 0; j < tux->wordLength; j++)
            {
                if(tux->choice == tux->word[j])
                {
                    matched = 1;
                    return matched;
                }
            }
        }

    }
    return matched;
}

int has_won(struct Penguin *tux)
{
    if(tux->win != 1)
    {
        int letters_guessed = 0;

        for(int i = 0; i < tux->wordLength; i++)
        {
            for(int j = 0; j < tux->indexLength; j++)
            {
                if((tux->word[i] == tux->index[j]) && (tux->word[i] != ' '))
                {
                    letters_guessed++;
                }
            }
            if(tux->word[i] == ' ')
            {
                letters_guessed++;
            }
        }

        if(letters_guessed == tux->wordLength)
        {
            return 1;
        }
    }

    return 0;
}

int check_full_guess(struct Penguin *tux)
{
    if(strcmp(tux->word, tux->s_choice) == 0)
    {
        return 1;
    }

    return 0;
}

int add_score(struct Penguin *tux)
{
    switch(tux->fails)
    {
        case 5:
            return 1;
        case 4:
            return 2;
        case 3:
            return 3;
        case 2:
            return 4;
        case 1:
            return 5;
        case 0:
            return 6;
    }

    return 0;
}

void print_str(char *str)
{
    int length = strlen(str);

    for(int i = 0; i < length; i++)
    {
        addch(str[i]);
    }
}
