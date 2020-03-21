#include "../include/menu_system.h"

void welcome_screen (struct Penguin *tux, struct Game_States *screen_data, const struct Game_Options *game_info)
{
    if (game_info->welcome == '0')
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
                wrefresh (game_info->tux_win);

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

void menu_system (struct Penguin *tux, struct Game_States *screen_data, struct Game_Options *game_info)
{
    if ( (tux->lives == 0) && (tux->option == '1'))                              // PLAYER LOST ENTIRE GAME
    {
        game_over_screen (tux, screen_data, game_info);
    }
    else                                            // THE GAME CONTINES
    {
        switch (tux->option)
        {
            case '1':                               // PLAY AGAIN PROMPT
                play_again_prompt (tux, screen_data, game_info);
                break;

            case '2':                               // RETURN TO MENU PROMPT
                about_screen (screen_data, game_info);
                break;

            case '3':
                game_info->play = '1';
                break;

            case '4':                               // EXITS ENTIRE GAME
                return_to_menu_screen (tux, screen_data->screen, game_info);
                break;
        }
    }
}

void game_over_screen (struct Penguin *tux, struct Game_States *screen_data, struct Game_Options *game_info)
{
    strcpy (screen_data->screen, "");
    strcat (screen_data->screen, screen_data->str9);
    correct_guesses_to_str (tux, screen_data->screen);
    failed_guesses_to_str (tux, screen_data->screen);

    do
        {
            clear ();
            game_info->color_option = 4;
            print_game_scr (&tux->score, &tux->lives, screen_data->screen, &game_info->color_option);
            attron (COLOR_PAIR (1));
            printw ("\n   Return to menu? (Y/n): ");
            attron (COLOR_PAIR (5));
            getstr (game_info->s_play);
            wrefresh (game_info->tux_win);

            check_response (game_info->s_play, &game_info->play, &game_info->welcome, '0', 1);
        }
    while ( (game_info->play != '0') && (game_info->play != '1'));
}

void play_again_prompt (struct Penguin *tux, struct Game_States *screen_data, struct Game_Options *game_info)
{
    do
        {
            clear ();
            print_game_scr (&tux->score, &tux->lives, screen_data->screen, &game_info->color_option);
            attron (COLOR_PAIR (1));
            printw ("\n   Press 'y' to get new word: ");
            attron (COLOR_PAIR (5));
            getstr (game_info->s_play);
            wrefresh (game_info->tux_win);

            check_response (game_info->s_play, &game_info->play, &game_info->welcome, '1', 0);
        }
    while ( (game_info->play != '0') && (game_info->play != '1'));
}

void about_screen (struct Game_States *screen_data, struct Game_Options *game_info)
{
    strcpy (screen_data->screen, "");
    strcat (screen_data->screen, screen_data->str10);

    do
        {
            clear ();
            print_str (screen_data->screen, 2);
            printw ("\n   Press 'y' to return to menu: ");
            getstr (game_info->s_play);
            wrefresh (game_info->tux_win);

            check_response (game_info->s_play, &game_info->play, &game_info->welcome, '0', 0);
        }
    while( (game_info->play != '0') && (game_info->play != '1'));
}

void return_to_menu_screen (struct Penguin *tux, char *screen, struct Game_Options *game_info)
{
    do
        {
            game_info->color_option = 1;
            print_game_scr (&tux->score, &tux->lives, screen, &game_info->color_option);
            attron (COLOR_PAIR (1));
            printw ("\n   Return to menu? (Y/n): ");
            attron (COLOR_PAIR (5));
            getstr (game_info->s_play);
            wrefresh (game_info->tux_win);

            check_response (game_info->s_play, &game_info->play, &game_info->welcome, '0', 1);
        }
    while ( (game_info->play != '0') && (game_info->play != '1'));
    tux->option = '1';
}

void check_response (char *s_play, char *play, char *welcome, char display_welcome_screen, int no_option)
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
    else if ( ((*play == 'n') || (*play == 'N')) && (no_option == 1))
    {
        *play = '1';
    }
    else
    {
        *play = ' ';
    }
}
