#ifndef GAME_DATA
#define GAME_DATA

#include <curses.h>

#define SIZE 256
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


struct Penguin
{
    char word[SIZE], index[SIZE], failedGuesses[SIZE], s_option[SIZE], s_choice[SIZE], choice, **words;
    unsigned long int wordLength, fails, indexLength, win, letters_guessed, score, max_score, lives, option;
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
};

struct Game_Options
{
    WINDOW *tux_win;
    char s_play[SIZE];
    int did_open, wordCount, pickLine, color_option, play, welcome;
};

#endif
