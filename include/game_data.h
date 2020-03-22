#ifndef GAME_DATA
#define GAME_DATA

#include <curses.h>

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

#define GAME_SCREEN 1
#define ABOUT_SCREEN 2
#define QUIT_GAME 3
#define RETURN_TO_MENU_PROMPT 4
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


struct Penguin
{
    char word[SIZE];
    char index[SIZE];
    char failedGuesses[SIZE];
    char s_option[SIZE];
    char s_choice[SIZE];
    char choice;
    char **words;
    unsigned long int wordLength;
    unsigned long int fails;
    unsigned long int indexLength;
    unsigned long int win;
    unsigned long int letters_guessed;
    unsigned long int score;
    unsigned long int max_score;
    unsigned long int lives;
    unsigned long int option;
};

struct Game_States
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
};

struct Game_Options
{
    char s_play[SIZE];
    int did_open;
    int wordCount;
    int pickLine;
    int color_option;
    int play;
    int welcome;
    int set_color;
};

#endif
