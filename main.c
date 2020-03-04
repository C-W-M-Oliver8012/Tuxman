#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define CLEAR for(int i = 0; i < 100; i++){ printf("\n"); }

void print_file(char *filename)
{
    // CREATES POINTER TO FILE
    FILE *file;

    // LINE BUFF OF FILE
    char buff[255];

    // OPENS GRAPHICS FILE
    file = fopen(filename, "a+");

    // LOOPS UNTIL EVERY LINE HAS BEEN PRINTED
    while(fgets(buff, 255, (FILE*)file))
    {
        // PRINTS EACH LINE
        printf("%s", buff);
    }

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
    while(fgets(word, 255, (FILE*)file))
    {
        wordCount++;
    }

    // SEEDS RAND
    time_t t;
    srand((unsigned) time(&t));
    // PICKS RANDOM NUMBER
    int pickLine = rand() % wordCount + 1;

    // GETS RANDOM WORD
    wordCount = 0;
    file = fopen("data/words.txt", "a+");
    while(fgets(word, 255, (FILE*)file) && wordCount < pickLine)
    {
        wordCount++;
    }

    // CLOSES FILE
    fclose(file);
}

void print_guess(char *word, int *wordLength, char *index, int *indexLength, char *failedGuesses, int *fails, int *win)
{
    // USED TO DETERMINE IF A PLAYER HAS WON THE GAME OR NOT
    int letters_guessed = 0;

    // SPACE FOR FORMATTING
    printf("   ");

    // index loop
    for(int i = 0; i < *wordLength; i++)
    {
        // USED TO DETERMINE IF CHAR IN INDEX WAS FOUND OR NOT && USED TO DETERMINE SPACES
        int matched = 0;

        // IF GAME IS OVER AND THE CURRENT LETTER IS NOT A SPACE
        if((*fails == 7) && (word[i] != ' '))
        {
            printf("%c ", word[i]);
            matched++;
        }
        // SAME AS PREVIOUS EXCEPT CURRENT LETTER IS A SPACE
        else if((*fails == 7) && (word[i] == ' '))
        {
            printf("    ");
            matched++;
        }

        // IF GAME IS NOT OVER && INDEX LENGTH IS NOT ZERO && LETTER ISN'T A SPACE
        if(*fails != 7 && *indexLength != 0 && (word[i] != ' '))
        {
            // INDEX LOOP
            for(int j = 0; j < *indexLength; j++)
            {
                // CURRENT LETTER GUESSED MATCHES WORD LETTER AND GUESSES ARE LEFT
                if(word[i] == index[j])
                {
                    // PRINTS GUESSED LETTER
                    printf("%c ", word[i]);
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
        else if((word[i] == ' ') && (*fails != 7))
        {
            printf("    ");
            letters_guessed++;
        }
    }

    // PRINTS THE UNDERSCORES
    printf("\n   ");
    for(int i = 0; i < *wordLength; i++)
    {
        if(word[i] != ' ')
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
    for(int i = 0; i < *fails; i++)
    {
        printf("%c ", failedGuesses[i]);
    }

    // COMPARES letters_guessed TO THE LENGTH OF THE WORD TO DETERMINE IF PLAYER WON
    if(letters_guessed == *wordLength)
    {
        *win = 1;
    }
}

void get_guess(char *word, int *wordLength, char *index, int *indexLength, char *failedGuesses, int *fails, char *option)
{
    // USER INPUT
    char s_choice[7];
    // SINGLE CHARACTER THAT USER GUESSED
    char choice;
    // USED TO DETERMINE IF CHOICE IS A GOOD GUESS
    int matched = 0;

    // GETS USER INPUT
    printf("\n   Pick a letter: ");
    fgets(s_choice, 7, stdin);
    choice = s_choice[0];

    // CHECKS IF INPUT IS VALID BASED ON LENGTH AND NEWLINE
    int checkIndex = 0;
    if(strlen(s_choice) > 2 || choice == '\n')
    {
        checkIndex = 1;
    }

    // CHECKS IF INPUT IS IN INDEX ARRAY
    for(int i = 0; i < *indexLength; i++)
    {
        if(choice == index[i])
        {
            checkIndex = 1;
        }
    }

    // CHECKS IF INPUT IS IN failedGuesses ARRAY
    for(int i = 0; i < *fails; i++)
    {
        if(choice == failedGuesses[i])
        {
            checkIndex = 1;
        }
    }

    // IF INPUT IS VALID
    if(checkIndex != 1)
    {
        // INDEX LOOP
        for(int i = 0; i <= *indexLength; i++)
        {
            // WORD LOOP
            for(int j = 0; j < *wordLength; j++)
            {
                // IF THE CHOICE MATCHES CURRENT LETTER IN WORD
                if(choice == word[j])
                {
                    // MATCH EQUALS 1
                    matched = 1;
                    // CHOICE ADDED TO INDEX
                    index[*indexLength] = choice;
                    // BREAKS OUT OF LOOP
                    break;
                }
            }
        }

        // THE CHOICE WAS BAD AND IS ADDED TO failedGuesses ARRAY
        // FAILS INTEGER INCREASED BY 1
        if(matched == 0)
        {
            failedGuesses[*fails] = choice;
            *fails = *fails + 1;
        }
        // CHOICE WAS GOOD AND THE indexLength LENGTH INCREASES BY 1
        if(matched == 1)
        {
            *indexLength = *indexLength + 1;
        }
    }
    // ADDS ABILITY TO EXIT THE GAME
    if(choice == '^')
    {
        *fails = 7;
        *option = '3';
    }
}

int main()
{
    char s_play[7];
    char play = '0';
    char welcome = '0';

    char word[255], index[255], failedGuesses[255];
    int wordLength, fails, indexLength, win;


    while(play == '0')
    {
        // STRING OF USER INPUT
        char s_option[7];
        // CHAR TO DETERMINE OPTION
        char option;

        // CLEAR SCREEN AND PRINTS WELCOME SCREEN
        if(welcome == '0')
        {
            CLEAR
            print_file("graphics/Welcome.txt");
            // GETS INPUT FROM THE USER
            printf("\n   option: ");
            fgets(s_option, 7, stdin);
            // GETS SIMPLY CHAR FROM USER INPUT
            if(strlen(s_option) <= 2)
            {
                option = s_option[0];
            }
        }
        else
        {
            option = '1';
        }

        // THIS IS THE WORD TO BE GUESSED IN THE GAME
        get_word(word);
        // REMOVES NEWLINE
        strtok(word, "\n");
        // THIS IS THE LENGTH OF THE WORD BEING GUESSED
        wordLength = strlen(word);
        // THIS IS HOW MANY TIMES THE USER HAS GUESSED WRONG
        fails = 0;
        // THE AMOUNT OF CHARS IN index ARRAY
        indexLength = 0;
        // 0 = NOT WON && 1 = HAS WON
        win = 0;

        // GAME LOOP
        while((option == '1') && (fails != 7) && (win == 0))
        {
            /* the following loops contain all of
               the graphics which are displayed
               based on how often the user failed
            */
            if(fails == 0)
            {
                CLEAR
                print_file("graphics/hangman0.txt");
            }
            else if(fails == 1)
            {
                CLEAR
                print_file("graphics/hangman1.txt");
            }
            else if(fails == 2)
            {
                CLEAR
                print_file("graphics/hangman2.txt");
            }
            else if(fails == 3)
            {
                CLEAR
                print_file("graphics/hangman3.txt");
            }
            else if(fails == 4)
            {
                CLEAR
                print_file("graphics/hangman4.txt");
            }
            else if(fails == 5)
            {
                CLEAR
                print_file("graphics/hangman5.txt");
            }
            else if(fails == 6)
            {
                CLEAR
                print_file("graphics/hangman6.txt");
                fails = 7;
                // THIS PRINTS THE LETTERS GUESSED AS WELL AS THE FAILED GUESSES
                print_guess(word, &wordLength, index, &indexLength, failedGuesses, &fails, &win);
                break;
            }

            // THIS PRINTS THE LETTERS GUESSED AS WELL AS THE FAILED GUESSES
            print_guess(word, &wordLength, index, &indexLength, failedGuesses, &fails, &win);
            // THIS GETS THE NEXT GUESS IF THE USER HAS NOT WON YET
            if(win == 0)
            {
                get_guess(word, &wordLength, index, &indexLength, failedGuesses, &fails, &option);
            }
            else
            {
                CLEAR
                print_file("graphics/hangman7.txt");
                print_guess(word, &wordLength, index, &indexLength, failedGuesses, &fails, &win);
            }
        }
        // IF THE USER WAS ALREADY PLAYING THE GAME
        if(option == '1')
        {
            // PROMPTS USER TO PLAY AGAIN
            printf("\n   Play again? (y/n): ");
            // GETS USER INPUT
            fgets(s_play, 7, stdin);
            // CHECKS IF INPUT IS VALID
            if(strlen(s_play) <= 2)
            {
                play = s_play[0];
            }
            // PLAYER WANTS TO PLAY AGAIN
            if(play == 'y')
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
        else if(option == '2')
        {
            // CLEARS SCREEN AND GETS USER INPUT
            CLEAR
            print_file("graphics/about.txt");
            printf("   Return to menu? (y/n): ");
            fgets(s_play, 7, stdin);
            // CHECKS FOR INVALID INPUT
            if(strlen(s_play) <= 2)
            {
                play = s_play[0];
            }
            // PLAYER DOES NOT WANT TO RETURN TO MENU
            // ENDS GAME
            if(play == 'y')
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
        else if(option == '3')
        {
            // ENDS MENU LOOP
            play = '1';
        }
    }

    return 0;
}
