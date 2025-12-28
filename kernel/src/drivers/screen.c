#include "../include/drivers/screen.h"


int cursor_x = 0; // 0 - 79
int cursor_y = 0; // 0 - 24

screen_settings scr_settings;

void clear_screen(int colour) {
    volatile char *video = (volatile char*)START_ADDRESS;
    for(int i = 0;i<MAX_ROWS * MAX_COLS * 2;i+=2){
        video[i]= ' ';
        video[i+1] = colour;
    } 
    cursor_x = 0;
    cursor_y = 0;
    update_cursor(cursor_x, cursor_y);
}

void clear_line(int num, int colour) {
    volatile char *video = (volatile char*)(START_ADDRESS + num*MAX_COLS*2);
    for(int i=0; i<MAX_COLS*2;i+=2){
        video[i]= ' ';
        video[i+1] =colour;
    }
}

void clear_current_line(int colour) {
    volatile char *video = (volatile char*)(START_ADDRESS + cursor_y*MAX_COLS*2);
    for(int i=0; i<MAX_COLS*2;i+=2){
        video[i]= ' ';
        video[i+1] = colour;
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

    } else {
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

    update_cursor(cursor_x, cursor_y);
}

void print_string(const char* string, int kolor) {
    for(int i=0; string[i];i++) {
        print_char(string[i], kolor);
    }
}


void init_screen() {
    scr_settings.cursor_enabled = true;
    enable_cursor(14,15);
}

void update_cursor(int x, int y) {
    uint16_t pos = y * 80 + x; 

    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t)(pos & 0xFF));
    
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t)((pos >> 8) & 0xFF));
}

void enable_cursor(uint8_t cursor_start, uint8_t cursor_end)
{
	outb(0x3D4, 0x0A);
	outb(0x3D5, (inb(0x3D5) & 0xC0) | cursor_start);

	outb(0x3D4, 0x0B);
	outb(0x3D5, (inb(0x3D5) & 0xE0) | cursor_end);
}
