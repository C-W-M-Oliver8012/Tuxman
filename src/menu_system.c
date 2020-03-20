#include "../include/menu_system.h"

void print_game_scr (long unsigned int *score, long unsigned int *lives, char *screen, int *color_option)
{
    clear ();
    attron (COLOR_PAIR (1));
    printw ("\n   Score: ");
    attron (COLOR_PAIR (5));
    printw ("%d", *score);
    attron (COLOR_PAIR (2));
    printw ("                     Lives: ");
    attron (COLOR_PAIR (5));
    printw ("%d\n", *lives);
    print_str (screen, *color_option);
}

void welcome_screen (struct Penguin *tux, struct Game_States *screen_data, WINDOW *tux_win, char *welcome)
{
    if (*welcome == '0')
    {
        tux->score = 0;
        tux->lives = 5;
        tux->max_score = 10;
        strcat (screen_data->screen, screen_data->str0);
        strcat (screen_data->screen, "   Option: ");

        do
            {
                clear ();
                attron (COLOR_PAIR (5));
                print_str (screen_data->screen, 2);
                getstr (tux->s_option);
                wrefresh (tux_win);

                if (strlen (tux->s_option) < INPUT_SIZE)
                {
                    tux->option = tux->s_option[0];
                    if ( (tux->option != '1') && (tux->option != '2') && (tux->option != '3'))
                    {
                        tux->option = '0';
                    }
                }
                else
                {
                    tux->option = '0';
                }
            }
        while(tux->option == '0');
    }
}

void menu_system (struct Penguin *tux, struct Game_States *screen_data, int *color_option, char *s_play, char *play, char *welcome, WINDOW *tux_win)
{
    if ( (tux->lives == 0) && (tux->option == '1'))                              // PLAYER LOST ENTIRE GAME
    {
        game_over_screen (tux, screen_data, play, welcome, s_play, color_option, tux_win);
    }
    else                                            // THE GAME CONTINES
    {
        switch (tux->option)
        {
            case '1':                               // PLAY AGAIN PROMPT
                play_again_prompt (tux, screen_data, play, welcome, s_play, color_option, tux_win);
                break;

            case '2':                               // RETURN TO MENU PROMPT
                about_screen (screen_data, play, welcome, s_play, color_option, tux_win);
                break;

            case '3':
                *play = '1';
                break;

            case '4':                               // EXITS ENTIRE GAME
                return_to_menu_screen (tux, screen_data->screen, play, welcome, s_play, color_option, tux_win);
                break;
        }
    }
}

void game_over_screen (struct Penguin *tux, struct Game_States *screen_data, char *play, char *welcome, char *s_play, int *color_option, WINDOW *tux_win)
{
    strcpy (screen_data->screen, "");
    strcat (screen_data->screen, screen_data->str9);
    correct_guesses_to_str (tux, screen_data->screen);
    failed_guesses_to_str (tux, screen_data->screen);

    do
        {
            clear ();
            *color_option = 4;
            print_game_scr (&tux->score, &tux->lives, screen_data->screen, color_option);
            attron (COLOR_PAIR (1));
            printw ("\n   Return to menu? (Y/n): ");
            attron (COLOR_PAIR (5));
            getstr (s_play);
            wrefresh (tux_win);

            check_response (s_play, play, welcome, '0');
        }
    while ( (*play != '0') && (*play != '1'));
}

void play_again_prompt (struct Penguin *tux, struct Game_States *screen_data, char *play, char *welcome, char *s_play, int *color_option, WINDOW *tux_win)
{
    do
        {
            clear ();
            print_game_scr (&tux->score, &tux->lives, screen_data->screen, color_option);
            attron (COLOR_PAIR (1));
            printw ("\n   Play again? (Y/n): ");
            attron (COLOR_PAIR (5));
            getstr (s_play);
            wrefresh (tux_win);

            check_response (s_play, play, welcome, '1');
        }
    while ( (*play != '0') && (*play != '1'));
}

void about_screen (struct Game_States *screen_data, char *play, char *welcome, char *s_play, int *color_option, WINDOW *tux_win)
{
    strcpy (screen_data->screen, "");
    strcat (screen_data->screen, screen_data->str10);

    do
        {
            clear ();
            print_str (screen_data->screen, 2);
            printw ("   Return to menu? (Y/n): ");
            getstr (s_play);
            wrefresh (tux_win);

            check_response (s_play, play, welcome, '0');
        }
    while( (*play != '0') && (*play != '1'));
}

void return_to_menu_screen (struct Penguin *tux, char *screen, char *play, char *welcome, char *s_play, int *color_option, WINDOW *tux_win)
{
    do
        {
            *color_option = 1;
            print_game_scr (&tux->score, &tux->lives, screen, color_option);
            attron (COLOR_PAIR (1));
            printw ("\n   Return to menu? (Y/n): ");
            attron (COLOR_PAIR (5));
            getstr (s_play);
            wrefresh (tux_win);

            check_response (s_play, play, welcome, '0');
        }
    while ( (*play != '0') && (*play != '1'));
    tux->option = '1';
}

void check_response (char *s_play, char *play, char *welcome, char display_welcome_screen)
{
    if (strlen(s_play) < INPUT_SIZE)
    {
        *play = s_play[0];
    }
    else
    {
        *play = ' ';
    }

    if ( (*play == 'y') || (*play == 'Y'))
    {
        *play = '0';
        *welcome = display_welcome_screen;
    }
    else if ( (*play == 'n') || (*play == 'N'))
    {
        *play = '1';
    }
    else
    {
        *play = ' ';
    }
}
