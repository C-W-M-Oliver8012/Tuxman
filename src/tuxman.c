#include "../headers/functions.h"

int main()
{
    initscr();

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
            printw("   option: ");
            refresh();
            //fgets(tux.s_option, SIZE, stdin);
            getstr(tux.s_option);
            // GETS SIMPLY CHAR FROM USER INPUT
            if(strlen(tux.s_option) < INPUT_SIZE)
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
        // NUMBER OF LETTERS GUESSED USED TO DETERMINE IF GAME HAS BEEN WON
        tux.letters_guessed = 0;

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
                print_failed_guesses(&tux);
                refresh();
                break;
            }

            // THIS PRINTS THE LETTERS GUESSED AS WELL AS THE FAILED GUESSES
            print_guess(&tux);
            print_failed_guesses(&tux);
            refresh();
            // DETERMINES IF PLAYER HAS WON GAME
            has_won(&tux);
            // THIS GETS THE NEXT GUESS IF THE USER HAS NOT WON YET
            if(tux.win == 0)
            {
                get_guess(&tux);
                exit_game(&tux);
            }
            else
            {
                CLEAR
                print_file("graphics/tuxman7.txt");
                print_guess(&tux);
                print_failed_guesses(&tux);
            }
        }
        // IF THE USER WAS ALREADY PLAYING THE GAME
        if(tux.option == '1')
        {
            // PROMPTS USER TO PLAY AGAIN
            printw("\n   Play again? (Y/n): ");
            // GETS USER INPUT
            //fgets(s_play, SIZE, stdin);
            getstr(s_play);
            refresh();
            // CHECKS IF INPUT IS VALID
            if(strlen(s_play) < INPUT_SIZE)
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
            printw("   Return to menu? (Y/n): ");
            //fgets(s_play, SIZE, stdin);
            getstr(s_play);
            refresh();
            // CHECKS FOR INVALID INPUT
            if(strlen(s_play) < INPUT_SIZE)
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

    endwin();

    return 0;
}
