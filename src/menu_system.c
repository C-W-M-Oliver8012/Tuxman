#include "../include/menu_system.h"


void welcome_screen (Penguin *tux, const Game_States *screen_data, const Game_Options *game_info)
{
    if (game_info->welcome == TRUE)
    {
        tux->score = 0;
        tux->lives = 5;
        tux->max_score = 10;
        tux->category_has_been_set = FALSE;

        do
            {
                clear ();
                print_str (screen_data->str0, BROWN_FOR_MENU_SCREENS, &game_info->set_color);
                print_str_between_two_colors (GREEN_PAIR, WHITE_PAIR, "\n   Option: ", &game_info->set_color);
                getstr (tux->input);

                if (strlen (tux->input) < INPUT_SIZE)
                {
                    switch (tux->input[0])
                    {
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



void menu_system (Penguin *tux, Game_States *screen_data, Game_Options *game_info)
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



void game_over_screen (const Penguin *tux, Game_States *screen_data, Game_Options *game_info)
{
    strcpy (screen_data->screen, "");
    strcat (screen_data->screen, screen_data->str9);
    correct_guesses_to_str (tux, screen_data->screen);
    failed_guesses_to_str (tux, screen_data->screen);

    do
        {
            clear ();
            print_game_scr (tux, screen_data->screen, RED_FOR_LOSS_SCREEN, &game_info->set_color);
            print_str_between_two_colors (GREEN_PAIR, WHITE_PAIR, "\n   Return to menu? (Y/n): ", &game_info->set_color);
            getstr (game_info->input);

            check_response (game_info, TRUE, TRUE);
        }
    while ( (game_info->play != FALSE) && (game_info->play != TRUE));
}



void play_again_prompt (const Penguin *tux, const Game_States *screen_data, Game_Options *game_info)
{
    do
        {
            clear ();
            print_game_scr (tux, screen_data->screen, game_info->color_option, &game_info->set_color);
            print_str_between_two_colors (GREEN_PAIR, WHITE_PAIR, "\n   Press 'y' to get new word: ", &game_info->set_color);
            getstr (game_info->input);

            check_response (game_info, FALSE, FALSE);
        }
    while ( (game_info->play != FALSE) && (game_info->play != TRUE));
}



void about_screen (Game_States *screen_data, Game_Options *game_info)
{
    do
        {
            clear ();
            print_str (screen_data->str10, BROWN_FOR_MENU_SCREENS, &game_info->set_color);
            print_str_between_two_colors (GREEN_PAIR, WHITE_PAIR, "\n   Press 'y' to return to menu: ", &game_info->set_color);
            getstr (game_info->input);

            check_response (game_info, TRUE, FALSE);
        }
    while( (game_info->play != FALSE) && (game_info->play != TRUE));
}



void return_to_menu_screen (const Penguin *tux, char *screen, Game_Options *game_info)
{
    do
        {
            print_game_scr (tux, screen, BLUE_FOR_PENGUIN, &game_info->set_color);
            print_str_between_two_colors (GREEN_PAIR, WHITE_PAIR, "\n   Return to menu? (Y/n): ", &game_info->set_color);
            getstr (game_info->input);

            check_response (game_info, TRUE, TRUE);
        }
    while ( (game_info->play != FALSE) && (game_info->play != TRUE));
}



void check_response (Game_Options *game_info, const int display_welcome_screen, const int no_option)
{
    if (strlen(game_info->input) < INPUT_SIZE)
    {
        if ( (game_info->input[0] == 'y') || (game_info->input[0] == 'Y'))
        {
            game_info->play = TRUE;
            game_info->welcome = display_welcome_screen;
        }
        else if ( ((game_info->input[0] == 'n') || (game_info->input[0] == 'N')) && (no_option == TRUE))
        {
            game_info->play = FALSE;
        }
        else
        {
            game_info->play = NOT_FALSE_OR_TRUE;
        }
    }
    else
    {
        game_info->play = NOT_FALSE_OR_TRUE;
    }
}
