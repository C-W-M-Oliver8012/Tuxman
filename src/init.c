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



void get_screen_data (Game_States *screen_data, int *open)
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
    file_to_str ("graphics/choose_categories.txt", screen_data->str12, open);
}



void init_words (Penguin *tux, Game_States *screen_data, Game_Options *game_info, Categories *categories)
{
    categories->category_count = get_file_length ("data/categories.txt", &game_info->did_open);
    categories->filename = (char**)malloc (categories->category_count * sizeof (char*));
    categories->description = (char**)malloc (categories->category_count * sizeof (char*));
    categories->word_count = (int*)malloc (categories->category_count * sizeof (int));
    for (int i = 0; i < categories->category_count; i++)
    {
        categories->filename[i] = malloc (SIZE * sizeof (char));
        categories->description[i] = malloc (SIZE * sizeof (char));
    }
    get_categories_filename_description (categories, &game_info->did_open);
    categories->max_word_count = 0;
    for (int i = 0; i < categories->category_count; i++)
    {
        char temp_dir[NAME_SIZE];
        strcpy (temp_dir, "data/");
        strcat (temp_dir, categories->filename[i]);
        strcat (temp_dir, ".txt");
        categories->word_count[i] = get_file_length (temp_dir, &game_info->did_open);
        if (categories->word_count[i] > categories->max_word_count)
        {
            categories->max_word_count = categories->word_count[i];
        }
    }

    tux->words = (char***)malloc (categories->category_count * sizeof (char**));
    for (int i = 0; i < categories->category_count; i++)
    {
        tux->words[i] = (char**)malloc (categories->max_word_count * sizeof (char*));
        for (int j = 0; j < categories->max_word_count; j++)
        {
            tux->words[i][j] = malloc (SIZE * sizeof (char));
        }
    }
    for (int i = 0; i < categories->category_count; i++)
    {
        char temp_dir[NAME_SIZE];
        strcpy (temp_dir, "data/");
        strcat (temp_dir, categories->filename[i]);
        strcat (temp_dir, ".txt");
        get_words (temp_dir, tux->words[i], &categories->word_count[i], &game_info->did_open);
    }
}



void prompt_to_change_screen_size (char *win_resize_screen, const int *set_color)
{
    char input[SIZE];
    do
        {
            clear ();
            print_str (win_resize_screen, BROWN_FOR_MENU_SCREENS, set_color);
            print_str_between_two_colors (GREEN_PAIR, WHITE_PAIR, " Enter 'y' here: ", set_color);
            getstr (input);
            
            if (strlen (input) > INPUT_SIZE)
            {
                strcpy (input, " ");
            }
        }
    while(input[0] != 'y');
}
