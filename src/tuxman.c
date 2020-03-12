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
            tux.score = 0;
            tux.lives = 5;
            strcpy(tux.s_option, "     ");
            tux.option = ' ';
            clear();
            print_file("graphics/Welcome.txt");
            // GETS INPUT FROM THE USER
            printw("   option: ");
            //fgets(tux.s_option, SIZE, stdin);
            getstr(tux.s_option);
            // GETS SIMPLY CHAR FROM USER INPUT
            if(strlen(tux.s_option) < INPUT_SIZE)
            {
                tux.option = tux.s_option[0];
            }
            else
            {
                tux.option = '0';
            }
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
        // RESETS S_CHOICE
        strcpy(tux.s_choice, "    ");
        // RESETS CHOICE
        tux.choice = ' ';
        //  USED TO DETERMINE IF PLAYER HAS MADE GUESS FOR COMPLETE WORD
        unsigned guess = 0;

        // GAME LOOP
        while((tux.option == '1') && (tux.fails != 7) && (tux.win == 0))
        {
            clear();
            if(tux.fails == 6)
            {
                tux.lives = tux.lives - 1;
            }
            print_score_lives(&tux);
            /* the following loops contain all of
               the graphics which are displayed
               based on how often the user failed
            */
            switch (tux.fails)
            {
                case 0:
                    print_file("graphics/tuxman0.txt");
                    break;
                case 1:
                    print_file("graphics/tuxman1.txt");
                    break;
                case 2:
                    print_file("graphics/tuxman2.txt");
                    break;
                case 3:
                    print_file("graphics/tuxman3.txt");
                    break;
                case 4:
                    print_file("graphics/tuxman4.txt");
                    break;
                case 5:
                    print_file("graphics/tuxman5.txt");
                    break;
                case 6:
                    print_file("graphics/tuxman6.txt");
                    tux.fails = 7;
                    // THIS PRINTS THE LETTERS GUESSED AS WELL AS THE FAILED GUESSES
                    print_guess(&tux);
                    print_failed_guesses(&tux);
                    break;
            }

            if(tux.fails != 7)
            {
                // THIS PRINTS THE LETTERS GUESSED AS WELL AS THE FAILED GUESSES
                print_guess(&tux);
                print_failed_guesses(&tux);
                // DETERMINES IF PLAYER HAS WON GAME
                has_won(&tux);

                if(tux.choice == '@')
                {
                    get_full_guess(&tux);
                    guess++;
                }

                // THIS GETS THE NEXT GUESS IF THE USER HAS NOT WON YET
                if(tux.win == 0 && (tux.choice != '@'))
                {
                    get_guess(&tux);
                    exit_game(&tux);
                    clear();
                }

                if(guess == 1)
                {
                    guess = 0;
                    tux.choice = ' ';
                }

                if(tux.win == 1)
                {
                    clear();
                    add_score(&tux);
                    print_score_lives(&tux);
                    print_file("graphics/tuxman7.txt");
                    print_guess(&tux);
                    print_failed_guesses(&tux);
                }
            }
        }
        if(tux.lives == 0)
        {
            tux.option = '4';
        }
        // IF THE USER WAS ALREADY PLAYING THE GAME
        if(tux.option == '1')
        {
            do
            {
                // PROMPTS USER TO PLAY AGAIN
                printw("\n   Play again? (Y/n): ");
                // GETS USER INPUT
                getstr(s_play);
                // CHECKS IF INPUT IS VALID
                if(strlen(s_play) < INPUT_SIZE)
                {
                    play = s_play[0];
                }
                else
                {
                    play = ' ';
                }
                // PLAYER WANTS TO PLAY AGAIN
                if((play == 'y') || (play == 'Y'))
                {
                    play = '0';
                    welcome = '1';
                }
                else if((play == 'n') || (play == 'N'))
                {
                    play = '1';
                }
                clear();
            } while((play != '0') && (play != '1'));
        }
        // IF THE USER WAS ON THE ABOUT SCREEN
        else if(tux.option == '2')
        {
            // CLEARS SCREEN AND GETS USER INPUT
            clear();
            print_file("graphics/about.txt");
            printw("   Return to menu? (Y/n): ");
            getstr(s_play);
            // CHECKS FOR INVALID INPUT
            if(strlen(s_play) < INPUT_SIZE)
            {
                play = s_play[0];
            }
            else
            {
                play = '\n';
            }
            // PLAYER DOES NOT WANT TO RETURN TO MENU
            // ENDS GAME
            if((play == 'y') || (play == 'Y'))
            {
                play = '0';
                welcome = '0';
            }
            else if((play == 'n') || (play == 'N'))
            {
                play = '1';
            }
            else
            {
                play = '0';
                welcome = '1';
            }
        }
        // THE USER WANTS TO EXIT THE GAME
        else if(tux.option == '3')
        {
            // ENDS MENU LOOP
            play = '1';
        }
        else if(tux.option == '4')
        {
            clear();
            print_score_lives(&tux);
            print_file("graphics/tuxman8.txt");
            print_guess(&tux);
            print_failed_guesses(&tux);
            do
            {
                // PROMPTS USER TO PLAY AGAIN
                printw("\n   Return to menu? (Y/n): ");
                // GETS USER INPUT
                getstr(s_play);
                // CHECKS IF INPUT IS VALID
                if(strlen(s_play) < INPUT_SIZE)
                {
                    play = s_play[0];
                }
                else
                {
                    play = ' ';
                }
                // PLAYER WANTS TO PLAY AGAIN
                if((play == 'y') || (play == 'Y'))
                {
                    play = '0';
                    welcome = '0';
                }
                else if((play == 'n') || (play == 'N'))
                {
                    play = '1';
                }
                clear();
            } while((play != '0') && (play != '1'));
        }
    }

    endwin();

    return 0;
}
