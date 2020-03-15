#include "../headers/functions.h"

int main()
{
    initscr();

    char s_play[SIZE];
    char play = '0';
    char welcome = '0';
    char file_data[DATA_SIZE];

    struct Penguin tux;

    while(play == '0')
    {
        strcpy(file_data, "");

        // CLEAR SCREEN AND PRINTS WELCOME SCREEN
        if(welcome == '0')
        {
            tux.score = 0;
            tux.lives = 5;
            tux.max_score = 10;
            clear();
            get_file_data("graphics/Welcome.txt", file_data);
            // GETS INPUT FROM THE USER
            strcat(file_data, "   option: ");
            printw("%s", file_data);
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
            strcpy(file_data, "");
            if(tux.fails == 6)
            {
                tux.lives = tux.lives - 1;
            }

            switch (tux.fails)
            {
                case 0:
                    get_file_data("graphics/tuxman0.txt", file_data);
                    break;
                case 1:
                    get_file_data("graphics/tuxman1.txt", file_data);
                    break;
                case 2:
                    get_file_data("graphics/tuxman2.txt", file_data);
                    break;
                case 3:
                    get_file_data("graphics/tuxman3.txt", file_data);
                    break;
                case 4:
                    get_file_data("graphics/tuxman4.txt", file_data);
                    break;
                case 5:
                    get_file_data("graphics/tuxman5.txt", file_data);
                    break;
                case 6:
                    get_file_data("graphics/tuxman6.txt", file_data);
                    tux.fails = 7;
                    break;
            }

            // THIS PRINTS THE LETTERS GUESSED AS WELL AS THE FAILED GUESSES
            correct_guesses_to_str(&tux, file_data);
            failed_guesses_to_str(&tux, file_data);

            if(tux.fails != 7)
            {
                // DETERMINES IF PLAYER HAS WON GAME
                tux.win = has_won(&tux);

                if(tux.choice == '@')
                {
                    printw("   score: %d                     lives: %d\n", tux.score, tux.lives);
                    printw("%s", file_data);
                    printw("\n   Guess the word: ");
                    getstr(tux.s_choice);

                    tux.win = check_full_guess(&tux);
                    if(tux.win == 0)
                    {
                        tux.failedGuesses[tux.fails] = '@';
                        tux.fails = tux.fails + 1;
                    }
                    guess++;
                }

                // THIS GETS THE NEXT GUESS IF THE USER HAS NOT WON YET
                if((tux.win) == 0 && (tux.choice != '@'))
                {
                    printw("   score: %d                     lives: %d\n", tux.score, tux.lives);
                    printw("%s", file_data);
                    printw("\n   Pick a letter: ");
                    getstr(tux.s_choice);
                    if(strlen(tux.s_choice) < INPUT_SIZE)
                    {
                        tux.choice = tux.s_choice[0];
                        int valid = check_guess(&tux);
                        if(valid == 0)
                        {
                            tux.failedGuesses[tux.fails] = tux.choice;
                            tux.fails++;
                        }
                        else if(valid == 1)
                        {
                            // CHOICE ADDED TO INDEX
                            tux.index[tux.indexLength] = tux.choice;
                            tux.indexLength++;
                        }
                    }

                    // ADDS ABILITY TO EXIT THE GAME
                    if(tux.choice == '^')
                    {
                        // MEANS GAME IS OVER
                        tux.fails = 7;
                        // IMMEDIATLEY EXITS GAME
                        tux.option = '3';
                    }
                }

                if(guess == 1)
                {
                    guess = 0;
                    tux.choice = ' ';
                }

                if(tux.win == 1)
                {
                    strcpy(file_data, "");
                    int add = add_score(&tux);
                    tux.score = tux.score + add;
                    if(tux.score >= tux.max_score)
                    {
                        tux.lives++;
                        tux.max_score = tux.max_score + 10;
                    }
                    get_file_data("graphics/tuxman7.txt", file_data);
                    correct_guesses_to_str(&tux, file_data);
                    failed_guesses_to_str(&tux, file_data);
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
                clear();
                printw("   score: %d                     lives: %d\n", tux.score, tux.lives);
                printw("%s", file_data);
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
            } while((play != '0') && (play != '1'));
        }
        // IF THE USER WAS ON THE ABOUT SCREEN
        else if(tux.option == '2')
        {
            // CLEARS SCREEN AND GETS USER INPUT
            clear();
            strcpy(file_data, "");
            get_file_data("graphics/about.txt", file_data);
            printw("%s", file_data);
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
            strcpy(file_data, "");
            get_file_data("graphics/tuxman8.txt", file_data);
            correct_guesses_to_str(&tux, file_data);
            failed_guesses_to_str(&tux, file_data);
            
            do
            {
                clear();
                printw("   score: %d                     lives: %d\n", tux.score, tux.lives);
                printw("%s", file_data);
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
            } while((play != '0') && (play != '1'));
        }
    }

    endwin();

    return 0;
}
