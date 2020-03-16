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

        if(welcome == '0')
        {
            tux.score = 0;
            tux.lives = 5;
            tux.max_score = 10;
            clear();
            file_to_str("graphics/welcome.txt", file_data);
            strcat(file_data, "   option: ");
            print_str(file_data);
            getstr(tux.s_option);
            if(strlen(tux.s_option) < INPUT_SIZE)
            {
                tux.option = tux.s_option[0];
                if((tux.option != '1') && (tux.option != '2') && (tux.option != '3'))
                {
                    tux.option = '0';
                }
            }
            else
            {
                tux.option = '0';
            }
        }

        get_word(tux.word);
        strtok(tux.word, "\n");
        tux.wordLength = strlen(tux.word);
        tux.fails = 0;
        tux.indexLength = 0;
        tux.win = 0;
        tux.letters_guessed = 0;
        strcpy(tux.s_choice, "");
        tux.choice = ' ';

        while((tux.option == '1') && (tux.fails != 7) && (tux.win == 0))
        {
            clear();
            strcpy(file_data, "");
            if(tux.fails == 6)                          // PLAYER LOST AND THEREFOR LOSES A LIFE
            {
                tux.lives--;
            }

            switch (tux.fails)                          // GETS PROPER GRAPHIC TO PRINT
            {
                case 0:
                    file_to_str("graphics/tuxman0.txt", file_data);
                    break;
                case 1:
                    file_to_str("graphics/tuxman1.txt", file_data);
                    break;
                case 2:
                    file_to_str("graphics/tuxman2.txt", file_data);
                    break;
                case 3:
                    file_to_str("graphics/tuxman3.txt", file_data);
                    break;
                case 4:
                    file_to_str("graphics/tuxman4.txt", file_data);
                    break;
                case 5:
                    file_to_str("graphics/tuxman5.txt", file_data);
                    break;
                case 6:
                    file_to_str("graphics/tuxman6.txt", file_data);
                    tux.fails = 7;
                    break;
            }

            correct_guesses_to_str(&tux, file_data);
            failed_guesses_to_str(&tux, file_data);

            if((tux.fails != 7) && (tux.win == 0))      // HASN'T LOST YET & HASN'T WON YET
            {
                if(tux.choice == '@')                   // GUESS ENTIRE WORD
                {
                    printw("   score: %d                     lives: %d\n", tux.score, tux.lives);
                    print_str(file_data);
                    printw("\n   Guess the word: ");
                    getstr(tux.s_choice);

                    tux.win = check_full_guess(&tux);
                    if(tux.win == 0)                    // wrong guess
                    {
                        tux.failedGuesses[tux.fails] = '@';
                        tux.fails = tux.fails + 1;
                        tux.choice = '^';
                        strcpy(tux.s_choice, "");
                    }
                    else                                // you win and all letters in word are added to index
                    {
                        for(int i = 0; i < tux.wordLength; i++)
                        {
                            int matched = 0;

                            for(int j = 0; j < tux.indexLength; j++)
                            {
                                if((tux.word[i] == tux.index[j]) || (tux.word[i] == ' '))
                                {
                                    matched = 1;
                                }
                            }

                            if(matched == 0)
                            {
                                tux.index[tux.indexLength] = tux.word[i];
                                tux.indexLength++;
                            }
                        }
                    }
                }
                else                                    // NORMAL TURN
                {
                    printw("   score: %d                     lives: %d\n", tux.score, tux.lives);
                    print_str(file_data);
                    printw("\n   Pick a letter: ");
                    getstr(tux.s_choice);
                    if(strlen(tux.s_choice) < INPUT_SIZE)
                    {
                        tux.choice = tux.s_choice[0];
                        int valid;
                        if(check_guess_is_valid(&tux) == 0)
                        {
                            valid = check_guess(&tux);
                        }
                        else
                        {
                            valid = 3;
                        }
                        if(valid == 0)
                        {
                            tux.failedGuesses[tux.fails] = tux.choice;
                            tux.fails++;
                        }
                        else if(valid == 1)
                        {
                            tux.index[tux.indexLength] = tux.choice;
                            tux.indexLength++;
                        }

                        tux.win = has_won(&tux);
                    }

                    if(tux.choice == '^')                // ENDS GAME
                    {
                        tux.fails = 7;
                        tux.option = '4';
                    }
                }

                if(tux.win == 1)                        // PLAYER WINS
                {
                    strcpy(file_data, "");
                    int add = add_score(&tux);
                    tux.score = tux.score + add;
                    int diff = tux.score - tux.max_score;
                    while(diff >= 10)
                    {
                        tux.lives++;
                        tux.max_score = tux.max_score + 10;
                        diff = tux.score - tux.max_score;
                    }
                    if(tux.score >= tux.max_score)
                    {
                        tux.lives++;
                        tux.max_score = tux.max_score + 10;
                    }
                    file_to_str("graphics/tuxman7.txt", file_data);
                    correct_guesses_to_str(&tux, file_data);
                    failed_guesses_to_str(&tux, file_data);
                }
            }
        }

        if(tux.lives == 0)                              // PLAYER LOST ENTIRE GAME
        {
            strcpy(file_data, "");
            file_to_str("graphics/tuxman8.txt", file_data);
            correct_guesses_to_str(&tux, file_data);
            failed_guesses_to_str(&tux, file_data);

            do
            {
                clear();
                printw("   score: %d                     lives: %d\n", tux.score, tux.lives);
                print_str(file_data);
                printw("\n   Return to menu? (Y/n): ");
                getstr(s_play);
                if(strlen(s_play) < INPUT_SIZE)
                {
                    play = s_play[0];
                }
                else
                {
                    play = ' ';
                }
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
        else                                            // THE GAME CONTINES
        {
            switch(tux.option)
            {
                case '1':                               // PLAY AGAIN PROMPT
                    do
                    {
                        clear();
                        printw("   score: %d                     lives: %d\n", tux.score, tux.lives);
                        print_str(file_data);
                        printw("\n   Play again? (Y/n): ");
                        getstr(s_play);
                        if(strlen(s_play) < INPUT_SIZE)
                        {
                            play = s_play[0];
                        }
                        else
                        {
                            play = ' ';
                        }
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
                    break;
                case '2':                               // RETURN TO MENU PROMPT
                    clear();
                    strcpy(file_data, "");
                    file_to_str("graphics/about.txt", file_data);
                    print_str(file_data);
                    printw("   Return to menu? (Y/n): ");
                    getstr(s_play);
                    if(strlen(s_play) < INPUT_SIZE)
                    {
                        play = s_play[0];
                    }
                    else
                    {
                        play = '\n';
                    }
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
                    break;
                case '3':
                    play = '1';
                    break;
                case '4':                               // EXITS ENTIRE GAME
                    do
                    {
                        clear();
                        printw("   score: %d                     lives: %d\n", tux.score, tux.lives);
                        print_str(file_data);
                        printw("\n   Return to menu? (Y/n): ");
                        getstr(s_play);
                        if(strlen(s_play) < INPUT_SIZE)
                        {
                            play = s_play[0];
                        }
                        else
                        {
                            play = ' ';
                        }
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
    }

    endwin();

    return 0;
}
