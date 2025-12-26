#ifndef SCREEN_H
#define SCREEN_H

#include <stdint.h>
#include <stdbool.h>

#define START_ADDRESS 0xB8000
#define MAX_ROWS 25
#define MAX_COLS 80


typedef struct {
    bool cursor_enabled;
} screen_settings;



void clear_screen(int colour);
void clear_line(int num, int colour);  // num 0 - 24
void clear_current_line(int colour);
void print_char(char c, int colour);
void print_string(const char* string, int colour);
void init_screen();
void update_cursor(int x, int y);
void enable_cursor(uint8_t cursor_start, uint8_t cursor_end);
#endif