/*
MIT License

Copyright (c) 2020 Caden Wayne Miller

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef GAME_DATA
#define GAME_DATA

#define DIR "/usr/share/tuxman/"

#define SIZE 256
#define NAME_SIZE 512
#define DATA_SIZE 12800
#define WORD_SIZE 12800
#define INPUT_SIZE 2

#define COLOR_BROWN 10
#define COLOR_LBLUE 11

#define TRUE 1
#define FALSE 0
#define NOT_FALSE_OR_TRUE 2

#define WELCOME_SCREEN 1
#define GAME_SCREEN 2
#define ABOUT_SCREEN 3
#define QUIT_GAME 4
#define RETURN_TO_MENU_PROMPT 5
#define INCORRECT_INPUT 0

#define GREEN_PAIR 1
#define RED_PAIR 2
#define BLUE_PAIR 3
#define YELLOW_PAIR 4
#define WHITE_PAIR 5
#define BROWN_PAIR 6

#define BLUE_FOR_PENGUIN 1
#define BROWN_FOR_MENU_SCREENS 2
#define GREEN_FOR_WIN_SCREEN 3
#define RED_FOR_LOSS_SCREEN 4


typedef struct Penguin
{
    char word[SIZE];
    char index[SIZE];
    char failedGuesses[SIZE];
    char input[SIZE];
    char choice;
    char ***words;
    int category_has_been_set;
    int category_choice;
    int wordLength;
    int fails;
    int indexLength;
    int win;
    int letters_guessed;
    unsigned long int score;
    int max_score;
    int lives;
    int option;
} Penguin;



typedef struct Game_States
{
    char screen[DATA_SIZE];
    char str0[DATA_SIZE];
    char str1[DATA_SIZE];
    char str2[DATA_SIZE];
    char str3[DATA_SIZE];
    char str4[DATA_SIZE];
    char str5[DATA_SIZE];
    char str6[DATA_SIZE];
    char str7[DATA_SIZE];
    char str8[DATA_SIZE];
    char str9[DATA_SIZE];
    char str10[DATA_SIZE];
    char str11[DATA_SIZE];
    char str12[DATA_SIZE];
} Game_States;



typedef struct Game_Options
{
    char input[SIZE];
    int did_open;
    int pickLine;
    int color_option;
    int play;
    int set_color;
} Game_Options;



typedef struct Categories
{
    int category_count;
    int *word_count;
    int max_word_count;
    char **filename;
    char **description;
} Categories;



#endif
