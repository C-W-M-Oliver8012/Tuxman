#include "../headers/functions.h"

// PRINTS GRAPHICS FILES
void get_file_data(char *filename, char *file_data)
{
    // CREATES POINTER TO FILE
    FILE *file;

    // LINE BUFF OF FILE
    char buff[SIZE];
    // OPENS GRAPHICS FILE
    file = fopen(filename, "a+");

    // LOOPS UNTIL EVERY LINE HAS BEEN PRINTED
    while(fgets(buff, SIZE, (FILE*)file))
    {
        // PRINTS EACH LINE
        strcat(file_data, buff);
    }
    strcat(file_data, "\n");

    // CLOSES FILE
    fclose(file);
}

// RANDOMLY DETERMINES WHICH WORD TO SELECT FROM FILE
void get_word(char *word)
{
    // CREATES POINTER TO FILE
    FILE *file;

    // OPENS WORDS FILE
    file = fopen("data/words.txt", "a+");

    int wordCount = 0;
    while(fgets(word, SIZE, (FILE*)file))
    {
        wordCount++;
    }

    // SEEDS RAND
    time_t t;
    srand((unsigned) time(&t));
    // PICKS RANDOM NUMBER
    int pickLine = rand() % wordCount + 1;

    // GETS RANDOM WORD
    wordCount = 1;
    file = fopen("data/words.txt", "a+");
    while(fgets(word, SIZE, (FILE*)file) && wordCount < pickLine)
    {
        wordCount++;
    }

    // CLOSES FILE
    fclose(file);
}

// PRINTS THE LETTERS GUESSED CORECTLY
void correct_guesses_to_str(struct Penguin *tux, char *guess_data)
{
    // SPACE FOR FORMATTING
    strcat(guess_data, "   ");
    char formated_letters[SIZE];

    // LOOPS THROUGH INDEX
    for(int i = 0; i < tux->wordLength; i++)
    {
        // USED TO DETERMINE IF CHAR IN INDEX WAS FOUND OR NOT && USED TO DETERMINE SPACES
        int matched = 0;

        // IF GAME IS OVER AND THE CURRENT LETTER IS NOT A SPACE
        if(((tux->fails == 7) && (tux->word[i] != ' ')) || (tux->win == 1))
        {
            strcpy(formated_letters, "");
            formated_letters[0] = tux->word[i];
            formated_letters[1] = ' ';
            formated_letters[2] = '\0';
            strcat(guess_data, formated_letters);
            matched++;
        }
        // SAME AS PREVIOUS EXCEPT CURRENT LETTER IS A SPACE
        else if(((tux->fails == 7) && (tux->word[i] == ' ')) || (tux->win == 1))
        {
            strcat(guess_data, "  ");
            matched++;
        }

        // IF GAME IS NOT OVER && INDEX LENGTH IS NOT ZERO && LETTER ISN'T A SPACE
        if(tux->fails != 7 && tux->indexLength != 0 && (tux->word[i] != ' ') && (tux->win != 1))
        {
            // INDEX LOOP
            for(int j = 0; j < tux->indexLength; j++)
            {
                // CURRENT LETTER GUESSED MATCHES WORD LETTER AND GUESSES ARE LEFT
                if(tux->word[i] == tux->index[j])
                {
                    // PRINTS GUESSED LETTER
                    strcpy(formated_letters, "");
                    formated_letters[0] = tux->word[i];
                    formated_letters[1] = ' ';
                    formated_letters[2] = '\0';
                    strcat(guess_data, formated_letters);
                    // BREAKS OUT BECAUSE MATCH DETECTED
                    matched++;
                    break;
                }
            }
            // NOT IN INDEX
            if(matched == 0)
            {
                strcat(guess_data, "  ");
            }
        }
        // IF LETTER IS A SPACE
        else if((tux->word[i] == ' ') && (tux->fails != 7) && (tux->win != 1))
        {
            strcat(guess_data, "  ");
        }
    }

    // PRINTS THE UNDERSCORES
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

    // PRINTS THE FAILED GUESES
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

// GETS GUESS AND ADDS TO INDEX IF NEEDED
int check_guess(struct Penguin *tux)
{
    // USED TO DETERMINE IF CHOICE IS A GOOD GUESS
    int matched = 0;
    // CHECKS IF INPUT IS VALID BASED ON LENGTH AND NEWLINE
    int checkIndex = 0;

    if((tux->choice == '\0') || (tux->choice == ' ') || (tux->choice == '@') || (tux->choice == '^') || (strlen(tux->s_choice) > INPUT_SIZE) || (tux->choice == '\n'))
    {
        checkIndex = 1;
        matched = 3;
    }

    // CHECKS IF INPUT IS IN INDEX ARRAY
    for(int i = 0; i < tux->indexLength; i++)
    {
        if(tux->choice == tux->index[i])
        {
            checkIndex = 1;
            matched = 3;
        }
    }

    // CHECKS IF INPUT IS IN failedGuesses ARRAY
    for(int i = 0; i < tux->fails; i++)
    {
        if(tux->choice == tux->failedGuesses[i])
        {
            checkIndex = 1;
            matched = 3;
        }
    }

    // IF INPUT IS VALID
    if(checkIndex != 1)
    {
        // INDEX LOOP
        for(int i = 0; i <= tux->indexLength; i++)
        {
            // WORD LOOP
            for(int j = 0; j < tux->wordLength; j++)
            {
                // IF THE CHOICE MATCHES CURRENT LETTER IN WORD
                if(tux->choice == tux->word[j])
                {
                    // MATCH EQUALS 1
                    matched = 1;
                    return matched;
                }
            }
        }

    }
    return matched;
}

// DETERMINES IF PLAYER HAS WON
int has_won(struct Penguin *tux)
{
    if(tux->win != 1)
    {
        // RESETS LETTERS_GUESSED
        int letters_guessed = 0;

        // LOOP THROUGH ALL OF LETTERS IN WORD
        for(int i = 0; i < tux->wordLength; i++)
        {
            // LOOP THROUGH ALL LETTERS IN THE INDEX
            for(int j = 0; j < tux->indexLength; j++)
            {
                // INCREASE LETTERS GUESSED IF WORD MATCHES INDEX AND WORD IS NOT SPACE
                if((tux->word[i] == tux->index[j]) && (tux->word[i] != ' '))
                {
                    letters_guessed++;
                }
            }
            // IF WORD IS A SPACE, INCREASE LETTERS GUESSED
            if(tux->word[i] == ' ')
            {
                letters_guessed++;
            }
        }

        // IF LETTERS GUESSED EQUALS THE LENGTH OF WORD, THEN GAME IS WON
        if(letters_guessed == tux->wordLength)
        {
            // SETS GAME TO WON
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
