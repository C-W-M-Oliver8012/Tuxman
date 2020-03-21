#ifndef GAME_DATA
#define GAME_DATA

#include <curses.h>

#define SIZE 256
#define DATA_SIZE 12800
#define WORD_SIZE 12800
#define INPUT_SIZE 2
#define COLOR_BROWN 10
#define COLOR_LBLUE 11

struct Penguin
{
    char word[SIZE], index[SIZE], failedGuesses[SIZE], s_option[SIZE], option, s_choice[SIZE], choice, **words;
    unsigned long int wordLength, fails, indexLength, win, letters_guessed, score, max_score, lives;
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
    char s_play[SIZE], play, welcome;
    int open, wordCount, pickLine, color_option;
};

#endif
