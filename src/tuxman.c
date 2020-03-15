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
            get_file_data("graphics/Welcome.txt", file_data);
            strcat(file_data, "   option: ");
            print_str(file_data);
            getstr(tux.s_option);
            if(strlen(tux.s_option) < INPUT_SIZE)
            {
                tux.option = tux.s_option[0];
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
        unsigned guess = 0;

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

            correct_guesses_to_str(&tux, file_data);
            failed_guesses_to_str(&tux, file_data);

            if(tux.fails != 7)
            {
                tux.win = has_won(&tux);

                if(tux.choice == '@')
                {
                    printw("   score: %d                     lives: %d\n", tux.score, tux.lives);
                    print_str(file_data);
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

                if((tux.win) == 0 && (tux.choice != '@'))
                {
                    printw("   score: %d                     lives: %d\n", tux.score, tux.lives);
                    print_str(file_data);
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
                            tux.index[tux.indexLength] = tux.choice;
                            tux.indexLength++;
                        }
                    }

                    if(tux.choice == '^')
                    {
                        tux.fails = 7;
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

        switch(tux.option)
        {
            case '1':
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
            case '2':
                clear();
                strcpy(file_data, "");
                get_file_data("graphics/about.txt", file_data);
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
            case '4':
                strcpy(file_data, "");
                get_file_data("graphics/tuxman8.txt", file_data);
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
                break;
        }
    }

    endwin();

    return 0;
}
