#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define CLEAR for(int i = 0; i < 100; i++){ printf("\n"); }
#define SIZE 256

struct Penguin
{
    char word[SIZE], index[SIZE], failedGuesses[SIZE], s_option[SIZE], option;
    int wordLength, fails, indexLength, win;
};

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
        printf("%s", buff);
    }
    printf("\n");

    // CLOSES FILE
    fclose(file);
}

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

void print_guess(struct Penguin *tux)
{
    // USED TO DETERMINE IF A PLAYER HAS WON THE GAME OR NOT
    int letters_guessed = 0;

    // SPACE FOR FORMATTING
    printf("   ");

    // index loop
    for(int i = 0; i < tux->wordLength; i++)
    {
        // USED TO DETERMINE IF CHAR IN INDEX WAS FOUND OR NOT && USED TO DETERMINE SPACES
        int matched = 0;

        // IF GAME IS OVER AND THE CURRENT LETTER IS NOT A SPACE
        if((tux->fails == 7) && (tux->word[i] != ' '))
        {
            printf("%c ", tux->word[i]);
            matched++;
        }
        // SAME AS PREVIOUS EXCEPT CURRENT LETTER IS A SPACE
        else if((tux->fails == 7) && (tux->word[i] == ' '))
        {
            printf("    ");
            matched++;
        }

        // IF GAME IS NOT OVER && INDEX LENGTH IS NOT ZERO && LETTER ISN'T A SPACE
        if(tux->fails != 7 && tux->indexLength != 0 && (tux->word[i] != ' '))
        {
            // INDEX LOOP
            for(int j = 0; j < tux->indexLength; j++)
            {
                // CURRENT LETTER GUESSED MATCHES WORD LETTER AND GUESSES ARE LEFT
                if(tux->word[i] == tux->index[j])
                {
                    // PRINTS GUESSED LETTER
                    printf("%c ", tux->word[i]);
                    // INCREASED LETTERS GUESSED COUNT
                    letters_guessed++;
                    // BREAKS OUT BECAUSE MATCH DETECTED
                    matched++;
                    break;
                }
            }
            // NOT IN INDEX
            if(matched == 0)
            {
                printf("  ");
            }
        }
        // IF LETTER IS A SPACE
        else if((tux->word[i] == ' ') && (tux->fails != 7))
        {
            printf("    ");
            letters_guessed++;
        }
    }

    // PRINTS THE UNDERSCORES
    printf("\n   ");
    for(int i = 0; i < tux->wordLength; i++)
    {
        if(tux->word[i] != ' ')
        {
            printf("- ");
        }
        else
        {
            printf("    ");
        }
    }

    // PRINTS THE FAILED GUESES
    printf("\n\n   Bad guesses: ");
    for(int i = 0; i < tux->fails; i++)
    {
        printf("%c ", tux->failedGuesses[i]);
    }

    // COMPARES letters_guessed TO THE LENGTH OF THE WORD TO DETERMINE IF PLAYER WON
    if(letters_guessed == tux->wordLength)
    {
        tux->win = 1;
    }
}

void get_guess(struct Penguin *tux)
{
    // USER INPUT
    char s_choice[SIZE];
    // SINGLE CHARACTER THAT USER GUESSED
    char choice;
    // USED TO DETERMINE IF CHOICE IS A GOOD GUESS
    int matched = 0;

    // GETS USER INPUT
    printf("\n   Pick a letter: ");
    fgets(s_choice, SIZE, stdin);
    choice = s_choice[0];

    // CHECKS IF INPUT IS VALID BASED ON LENGTH AND NEWLINE
    int checkIndex = 0;
    if(strlen(s_choice) > 2 || choice == '\n')
    {
        checkIndex = 1;
    }

    // CHECKS IF INPUT IS IN INDEX ARRAY
    for(int i = 0; i < tux->indexLength; i++)
    {
        if(choice == tux->index[i])
        {
            checkIndex = 1;
        }
    }

    // CHECKS IF INPUT IS IN failedGuesses ARRAY
    for(int i = 0; i < tux->fails; i++)
    {
        if(choice == tux->failedGuesses[i])
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
                if(choice == tux->word[j])
                {
                    // MATCH EQUALS 1
                    matched = 1;
                    // CHOICE ADDED TO INDEX
                    tux->index[tux->indexLength] = choice;
                    // BREAKS OUT OF LOOP
                    break;
                }
            }
        }

        // THE CHOICE WAS BAD AND IS ADDED TO failedGuesses ARRAY
        // FAILS INTEGER INCREASED BY 1
        if(matched == 0)
        {
            tux->failedGuesses[tux->fails] = choice;
            tux->fails = tux->fails + 1;
        }
        // CHOICE WAS GOOD AND THE indexLength LENGTH INCREASES BY 1
        if(matched == 1)
        {
            tux->indexLength = tux->indexLength + 1;
        }
    }
    // ADDS ABILITY TO EXIT THE GAME
    if(choice == '^')
    {
        tux->fails = 7;
        tux->option = '3';
    }
}

int main()
{
    char s_play[SIZE];
    char play = '0';
    char welcome = '0';

    struct Penguin tux;


    while(play == '0')
    {
        // CLEAR SCREEN AND PRINTS WELCOME SCREEN
        if(welcome == '0')
        {
            CLEAR
            print_file("graphics/Welcome.txt");
            // GETS INPUT FROM THE USER
            printf("   option: ");
            fgets(tux.s_option, SIZE, stdin);
            // GETS SIMPLY CHAR FROM USER INPUT
            if(strlen(tux.s_option) <= 2)
            {
                tux.option = tux.s_option[0];
            }
        }
        else
        {
            tux.option = '1';
        }

        // THIS IS THE WORD TO BE GUESSED IN THE GAME
        get_word(tux.word);
        // REMOVES NEWLINE
        strtok(tux.word, "\n");
        // THIS IS THE LENGTH OF THE WORD BEING GUESSED
        tux.wordLength = strlen(tux.word);
        // THIS IS HOW MANY TIMES THE USER HAS GUESSED WRONG
        tux.fails = 0;
        // THE AMOUNT OF CHARS IN index ARRAY
        tux.indexLength = 0;
        // 0 = NOT WON && 1 = HAS WON
        tux.win = 0;

        // GAME LOOP
        while((tux.option == '1') && (tux.fails != 7) && (tux.win == 0))
        {
            /* the following loops contain all of
               the graphics which are displayed
               based on how often the user failed
            */
            if(tux.fails == 0)
            {
                CLEAR
                print_file("graphics/tuxman0.txt");
            }
            else if(tux.fails == 1)
            {
                CLEAR
                print_file("graphics/tuxman1.txt");
            }
            else if(tux.fails == 2)
            {
                CLEAR
                print_file("graphics/tuxman2.txt");
            }
            else if(tux.fails == 3)
            {
                CLEAR
                print_file("graphics/tuxman3.txt");
            }
            else if(tux.fails == 4)
            {
                CLEAR
                print_file("graphics/tuxman4.txt");
            }
            else if(tux.fails == 5)
            {
                CLEAR
                print_file("graphics/tuxman5.txt");
            }
            else if(tux.fails == 6)
            {
                CLEAR
                print_file("graphics/tuxman6.txt");
                tux.fails = 7;
                // THIS PRINTS THE LETTERS GUESSED AS WELL AS THE FAILED GUESSES
                print_guess(&tux);
                break;
            }

            // THIS PRINTS THE LETTERS GUESSED AS WELL AS THE FAILED GUESSES
            print_guess(&tux);
            // THIS GETS THE NEXT GUESS IF THE USER HAS NOT WON YET
            if(tux.win == 0)
            {
                get_guess(&tux);
            }
            else
            {
                CLEAR
                print_file("graphics/tuxman7.txt");
                print_guess(&tux);
            }
        }
        // IF THE USER WAS ALREADY PLAYING THE GAME
        if(tux.option == '1')
        {
            // PROMPTS USER TO PLAY AGAIN
            printf("\n   Play again? (Y/n): ");
            // GETS USER INPUT
            fgets(s_play, SIZE, stdin);
            // CHECKS IF INPUT IS VALID
            if(strlen(s_play) <= 2)
            {
                play = s_play[0];
            }
            // PLAYER WANTS TO PLAY AGAIN
            if((play == 'y') || (play == 'Y'))
            {
                play = '0';
                welcome = '1';
            }
            else
            {
                play = '1';
            }
        }
        // IF THE USER WAS ON THE ABOUT SCREEN
        else if(tux.option == '2')
        {
            // CLEARS SCREEN AND GETS USER INPUT
            CLEAR
            print_file("graphics/about.txt");
            printf("   Return to menu? (Y/n): ");
            fgets(s_play, SIZE, stdin);
            // CHECKS FOR INVALID INPUT
            if(strlen(s_play) <= 2)
            {
                play = s_play[0];
            }
            // PLAYER DOES NOT WANT TO RETURN TO MENU
            // ENDS GAME
            if((play == 'y') || (play == 'Y'))
            {
                play = '0';
                welcome = '0';
            }
            else
            {
                play = '1';
            }
        }
        // THE USER WANTS TO EXIT THE GAME
        else if(tux.option == '3')
        {
            // ENDS MENU LOOP
            play = '1';
        }
    }

    return 0;
}
