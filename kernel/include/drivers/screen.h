#ifndef SCREEN_H
#define SCREEN_H

#define START_ADDRESS 0xB8000
#define MAX_ROWS 25
#define MAX_COLS 80


void clear_screen();
void clear_line(int num);  // num 0 - 24
void clear_current_line();
void print_char(char c, int colour);
void print_string(const char* string, int colour);

#endif