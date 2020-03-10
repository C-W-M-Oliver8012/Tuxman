#include "../headers/functions.h"

void print_score(struct Penguin *tux)
{
    printw("   score: %d\n", tux->score);
}

void add_score(struct Penguin *tux)
{
    if(tux->fails == 5)
    {
        tux->score = tux->score + 1;
    }
    else if(tux->fails == 4)
    {
        tux->score = tux->score + 2;
    }
    else if(tux->fails == 3)
    {
        tux->score = tux->score + 3;
    }
    else if(tux->fails == 2)
    {
        tux->score = tux->score + 4;
    }
    else if(tux->fails == 1)
    {
        tux->score = tux->score + 5;
    }
    else if(tux->fails == 0)
    {
        tux->score = tux->score + 6;
    }
}

// PRINTS GRAPHICS FILES
void print_file(char *filename)
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
        printw("%s", buff);
    }
    printw("\n");

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
void print_guess(struct Penguin *tux)
{
    // SPACE FOR FORMATTING
    printw("   ");

    // LOOPS THROUGH INDEX
    for(int i = 0; i < tux->wordLength; i++)
    {
        // USED TO DETERMINE IF CHAR IN INDEX WAS FOUND OR NOT && USED TO DETERMINE SPACES
        int matched = 0;

        // IF GAME IS OVER AND THE CURRENT LETTER IS NOT A SPACE
        if((tux->fails == 7) && (tux->word[i] != ' '))
        {
            printw("%c ", tux->word[i]);
            matched++;
        }
        // SAME AS PREVIOUS EXCEPT CURRENT LETTER IS A SPACE
        else if((tux->fails == 7) && (tux->word[i] == ' '))
        {
            printw("  ");
            matched++;
        }
        else if(tux->win == 1)
        {
            printw("%c ", tux->word[i]);
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
                    printw("%c ", tux->word[i]);
                    // BREAKS OUT BECAUSE MATCH DETECTED
                    matched++;
                    break;
                }
            }
            // NOT IN INDEX
            if(matched == 0)
            {
                printw("  ");
            }
        }
        // IF LETTER IS A SPACE
        else if((tux->word[i] == ' ') && (tux->fails != 7) && (tux->win != 1))
        {
            printw("  ");
        }
    }

    // PRINTS THE UNDERSCORES
    printw("\n   ");
    for(int i = 0; i < tux->wordLength; i++)
    {
        if(tux->word[i] != ' ')
        {
            printw("- ");
        }
        else
        {
            printw("  ");
        }
    }
}

// PRINTS FAILED GUESSES
void print_failed_guesses(struct Penguin *tux)
{
    // PRINTS THE FAILED GUESES
    printw("\n\n   Bad guesses: ");
    for(int i = 0; i < tux->fails; i++)
    {
        printw("%c ", tux->failedGuesses[i]);
    }
}

// GETS GUESS AND ADDS TO INDEX IF NEEDED
void get_guess(struct Penguin *tux)
{
    // USED TO DETERMINE IF CHOICE IS A GOOD GUESS
    int matched = 0;
    // CHECKS IF INPUT IS VALID BASED ON LENGTH AND NEWLINE
    int checkIndex = 0;

    // GETS USER INPUT
    printw("\n   Pick a letter: ");
    //fgets(tux->s_choice, SIZE, stdin);
    getstr(tux->s_choice);

    if(strlen(tux->s_choice) < INPUT_SIZE)
    {
        tux->choice = tux->s_choice[0];
    }
    else
    {
        checkIndex = 1;
    }

    if((tux->choice == '\0') || (tux->choice == ' ') || (tux->choice == '@'))
    {
        checkIndex = 1;
    }

    if((strlen(tux->s_choice) > INPUT_SIZE) || (tux->choice == '\n'))
    {
        checkIndex = 1;
    }

    // CHECKS IF INPUT IS IN INDEX ARRAY
    for(int i = 0; i < tux->indexLength; i++)
    {
        if(tux->choice == tux->index[i])
        {
            checkIndex = 1;
        }
    }

    // CHECKS IF INPUT IS IN failedGuesses ARRAY
    for(int i = 0; i < tux->fails; i++)
    {
        if(tux->choice == tux->failedGuesses[i])
        {
            checkIndex = 1;
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
                    // CHOICE ADDED TO INDEX
                    tux->index[tux->indexLength] = tux->choice;
                    // BREAKS OUT OF LOOP
                    break;
                }
            }
        }

        // THE CHOICE WAS BAD AND IS ADDED TO failedGuesses ARRAY
        // FAILS INTEGER INCREASED BY 1
        if(matched == 0)
        {
            tux->failedGuesses[tux->fails] = tux->choice;
            tux->fails = tux->fails + 1;
        }
        // CHOICE WAS GOOD AND THE indexLength LENGTH INCREASES BY 1
        if(matched == 1)
        {
            tux->indexLength = tux->indexLength + 1;
        }
    }
}

void get_full_guess(struct Penguin *tux)
{
    printw("\n   Guess the word: ");
    getstr(tux->s_choice);
    if(strcmp(tux->word, tux->s_choice) == 0)
    {
        tux->win = 1;
    }
    else
    {
        tux->failedGuesses[tux->fails] = '@';
        tux->fails = tux->fails + 1;
        clear();
    }
}

// DETERMINES IF PLAYER HAS WON
void has_won(struct Penguin *tux)
{
    if(tux->win != 1)
    {
        // RESETS LETTERS_GUESSED
        tux->letters_guessed = 0;

        // LOOP THROUGH ALL OF LETTERS IN WORD
        for(int i = 0; i < tux->wordLength; i++)
        {
            // LOOP THROUGH ALL LETTERS IN THE INDEX
            for(int j = 0; j < tux->indexLength; j++)
            {
                // INCREASE LETTERS GUESSED IF WORD MATCHES INDEX AND WORD IS NOT SPACE
                if((tux->word[i] == tux->index[j]) && (tux->word[i] != ' '))
                {
                    tux->letters_guessed = tux->letters_guessed + 1;
                }
            }
            // IF WORD IS A SPACE, INCREASE LETTERS GUESSED
            if(tux->word[i] == ' ')
            {
                tux->letters_guessed = tux->letters_guessed + 1;
            }
        }

        // IF LETTERS GUESSED EQUALS THE LENGTH OF WORD, THEN GAME IS WON
        if(tux->letters_guessed == tux->wordLength)
        {
            // SETS GAME TO WON
            tux->win = 1;
        }
    }
}

// CHECKS IF PLAYER WANTS TO EXIT THE GAME
void exit_game(struct Penguin *tux)
{
    // ADDS ABILITY TO EXIT THE GAME
    if(tux->choice == '^')
    {
        // MEANS GAME IS OVER
        tux->fails = 7;
        // IMMEDIATLEY EXITS GAME
        tux->option = '3';
    }
}
