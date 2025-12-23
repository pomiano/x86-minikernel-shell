#include "../include/drivers/screen.h"


int cursor_x = 0; // 0 - 79
int cursor_y = 0; // 0 - 24



void clear_screen() {
    volatile char *video = (volatile char*)START_ADDRESS;
    for(int i = 0;i<MAX_ROWS * MAX_COLS * 2;i+=2){
        video[i]= ' ';
        video[i+1] = 0x00;
    } 
    cursor_x = 0;
    cursor_y = 0;
}

void clear_line(int num) {
    volatile char *video = (volatile char*)(START_ADDRESS + num*MAX_COLS*2);
    for(int i=0; i<MAX_COLS*2;i+=2){
        video[i]= ' ';
        video[i+1] = 0x00;
    }
}

void clear_current_line() {
    volatile char *video = (volatile char*)(START_ADDRESS + cursor_y*MAX_COLS*2);
    for(int i=0; i<MAX_COLS*2;i+=2){
        video[i]= ' ';
        video[i+1] = 0x00;
    }
}

void print_char(char c, int colour) {
    int offset = 0;
    volatile char *video = (volatile char*)START_ADDRESS;
    if(c == '\n'){
        cursor_x = 0;
        cursor_y++;
    } else if(c == '\b'){
        if(cursor_x > 0)
            {
                cursor_x--;
                offset = (cursor_y * 80 + cursor_x) * 2;
                video[offset] = ' ';
                video[offset+1] = 0x0F;

            }

    }else {
        offset = (cursor_y * 80 + cursor_x) * 2;
        video[offset] = c;
        video[offset+1] = colour;

        cursor_x++;

        
    }
    if(cursor_x >= MAX_COLS){
        cursor_x = 0;
        cursor_y++;
    }
    if (cursor_y >= MAX_ROWS) {
        cursor_x = 0;
        cursor_y = 0; 
    }
}

void print_string(const char* string, int kolor) {
    for(int i=0; string[i];i++) {
        print_char(string[i], kolor);
    }
}
