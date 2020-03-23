#include "../include/menu_system.h"


void welcome_screen (struct Penguin *tux, struct Game_States *screen_data, const struct Game_Options *game_info)
{
    if (game_info->welcome == TRUE)
    {
        tux->score = 0;
        tux->lives = 5;
        tux->max_score = 10;
        strcat (screen_data->screen, screen_data->str0);

        do
            {
                clear ();
                print_str (screen_data->screen, BROWN_FOR_MENU_SCREENS, &game_info->set_color);
                if (game_info->set_color == TRUE)
                {
                    attron (COLOR_PAIR (WHITE_PAIR));
                }
                printw ("%s", "\n   Option: ");
                getstr (tux->s_option);

                if (strlen (tux->s_option) < INPUT_SIZE)
                {
                    switch (tux->s_option[0]) {
                        case '1':
                            tux->option = GAME_SCREEN;
                            break;
                        case '2':
                            tux->option = ABOUT_SCREEN;
                            break;
                        case '3':
                            tux->option = QUIT_GAME;
                            break;
                        default:
                            tux->option = INCORRECT_INPUT;
                    }
                }
                else
                {
                    tux->option = INCORRECT_INPUT;
                }
            }
        while(tux->option == INCORRECT_INPUT);
    }
}



void menu_system (struct Penguin *tux, struct Game_States *screen_data, struct Game_Options *game_info)
{
    if ( (tux->lives == 0) && (tux->option == 1))                              // PLAYER LOST ENTIRE GAME
    {
        game_over_screen (tux, screen_data, game_info);
    }
    else                                            // THE GAME CONTINES
    {
        switch (tux->option)
        {
            case GAME_SCREEN:                               // PLAY AGAIN PROMPT
                play_again_prompt (tux, screen_data, game_info);
                break;
            case ABOUT_SCREEN:                               // RETURN TO MENU PROMPT
                about_screen (screen_data, game_info);
                break;
            case QUIT_GAME:
                game_info->play = FALSE;
                break;
            case RETURN_TO_MENU_PROMPT:                               // EXITS ENTIRE GAME
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
            print_game_scr (&tux->score, &tux->lives, screen_data->screen, RED_FOR_LOSS_SCREEN, &game_info->set_color);
            if (game_info->set_color == TRUE)
            {
                attron (COLOR_PAIR (GREEN_PAIR));
            }
            printw ("\n   Return to menu? (Y/n): ");
            if (game_info->set_color == TRUE)
            {
                attron (COLOR_PAIR (WHITE_PAIR));
            }
            getstr (game_info->s_play);

            check_response (game_info->s_play, &game_info->play, &game_info->welcome, TRUE, TRUE);
        }
    while ( (game_info->play != FALSE) && (game_info->play != TRUE));
}



void play_again_prompt (struct Penguin *tux, struct Game_States *screen_data, struct Game_Options *game_info)
{
    do
        {
            clear ();
            print_game_scr (&tux->score, &tux->lives, screen_data->screen, game_info->color_option, &game_info->set_color);
            if (game_info->set_color == TRUE)
            {
                attron (COLOR_PAIR (GREEN_PAIR));
            }
            printw ("\n   Press 'y' to get new word: ");
            if (game_info->set_color == TRUE)
            {
                attron (COLOR_PAIR (WHITE_PAIR));
            }
            getstr (game_info->s_play);

            check_response (game_info->s_play, &game_info->play, &game_info->welcome, FALSE, FALSE);
        }
    while ( (game_info->play != FALSE) && (game_info->play != TRUE));
}



void about_screen (struct Game_States *screen_data, struct Game_Options *game_info)
{
    strcpy (screen_data->screen, "");
    strcat (screen_data->screen, screen_data->str10);

    do
        {
            clear ();
            print_str (screen_data->screen, BROWN_FOR_MENU_SCREENS, &game_info->set_color);
            if (game_info->set_color == TRUE)
            {
                attron (COLOR_PAIR (WHITE_PAIR));
            }
            printw ("\n   Press 'y' to return to menu: ");
            getstr (game_info->s_play);

            check_response (game_info->s_play, &game_info->play, &game_info->welcome, TRUE, FALSE);
        }
    while( (game_info->play != FALSE) && (game_info->play != TRUE));
}



void return_to_menu_screen (struct Penguin *tux, char *screen, struct Game_Options *game_info)
{
    do
        {
            print_game_scr (&tux->score, &tux->lives, screen, BLUE_FOR_PENGUIN, &game_info->set_color);
            if (game_info->set_color == TRUE)
            {
                attron (COLOR_PAIR (GREEN_PAIR));
            }
            printw ("\n   Return to menu? (Y/n): ");
            if (game_info->set_color == TRUE)
            {
                attron (COLOR_PAIR (WHITE_PAIR));
            }
            getstr (game_info->s_play);

            check_response (game_info->s_play, &game_info->play, &game_info->welcome, TRUE, TRUE);
        }
    while ( (game_info->play != FALSE) && (game_info->play != TRUE));
    tux->option = GAME_SCREEN;
}



void check_response (char *s_play, int *play, int *welcome, int display_welcome_screen, int no_option)
{
    if (strlen(s_play) < INPUT_SIZE)
    {
        if ( (s_play[0] == 'y') || (s_play[0] == 'Y'))
        {
            *play = TRUE;
            *welcome = display_welcome_screen;
        }
        else if ( ((s_play[0] == 'n') || (s_play[0] == 'N')) && (no_option == TRUE))
        {
            *play = FALSE;
        }
        else
        {
            *play = NOT_FALSE_OR_TRUE;
        }
    }
    else
    {
        *play = NOT_FALSE_OR_TRUE;
    }
}
