#include "../include/init.h"

void set_all_colors (int *set_color)
{
    if (has_colors () == TRUE)
    {
        start_color ();
        if (can_change_color () == TRUE)
        {
            init_color (COLOR_BLACK, 25, 25, 25);                                       // defines all colors used in program
            init_color (COLOR_GREEN, 262, 690, 164);
            init_color (COLOR_RED, 933, 219, 192);
            init_color (COLOR_BLUE, 0, 490, 729);
            init_color (COLOR_YELLOW, 882, 835, 333);
            init_color (COLOR_WHITE, 850, 850, 850);
            init_color (COLOR_BROWN, 600, 400, 50);
            init_pair (BROWN_PAIR, COLOR_BROWN, COLOR_BLACK);
        }
        else
        {
            init_pair (BROWN_PAIR, COLOR_MAGENTA, COLOR_BLACK);
        }

        init_pair (GREEN_PAIR, COLOR_GREEN, COLOR_BLACK);                                    // cerates all color pairs used in program
        init_pair (RED_PAIR, COLOR_RED, COLOR_BLACK);
        init_pair (BLUE_PAIR, COLOR_BLUE, COLOR_BLACK);
        init_pair (YELLOW_PAIR, COLOR_YELLOW, COLOR_BLACK);
        init_pair (WHITE_PAIR, COLOR_WHITE, COLOR_BLACK);

        *set_color = TRUE;
    }
    else
    {
        *set_color = FALSE;
    }
}

void get_screen_data (struct Game_States *screen_data, int *open)
{
    file_to_str ("graphics/welcome.txt", screen_data->str0, open);              // gets screen data from files
    file_to_str ("graphics/tuxman0.txt", screen_data->str1, open);
    file_to_str ("graphics/tuxman1.txt", screen_data->str2, open);
    file_to_str ("graphics/tuxman2.txt", screen_data->str3, open);
    file_to_str ("graphics/tuxman3.txt", screen_data->str4, open);
    file_to_str ("graphics/tuxman4.txt", screen_data->str5, open);
    file_to_str ("graphics/tuxman5.txt", screen_data->str6, open);
    file_to_str ("graphics/tuxman6.txt", screen_data->str7, open);
    file_to_str ("graphics/tuxman7.txt", screen_data->str8, open);
    file_to_str ("graphics/tuxman8.txt", screen_data->str9, open);
    file_to_str ("graphics/about.txt", screen_data->str10, open);
    file_to_str ("graphics/win_resize.txt", screen_data->str11, open);
}

void prompt_to_change_screen_size (char *win_resize_screen, const int *set_color)
{
    char input[SIZE];
    do
        {
            clear ();
            print_str (win_resize_screen, BROWN_FOR_MENU_SCREENS, set_color);
            if (*set_color == TRUE)
            {
                attron (COLOR_PAIR (GREEN_PAIR));
            }
            printw (" Enter 'y' here: ");
            if (*set_color == TRUE)
            {
                attron (COLOR_PAIR (WHITE_PAIR));
            }
            getstr (input);
            refresh ();
            if (strlen (input) > INPUT_SIZE)
            {
                strcpy (input, " ");
            }
        }
    while(input[0] != 'y');
}
