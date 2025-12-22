#include "../include/kernel.h"
#include "../include/arch/idt.h"
#include "../include/drivers/keyboard.h"

#define MAX_ROWS 25
#define MAX_COLS 80

//ctrl+alt+2
//xp /16bx 0x10000

int cursor_x = 0; // 0 - 79
int cursor_y = 0; // 0 - 24

static int START_ADDRESS = 0xB8000;

void clear_screen() {
    volatile char *video = (volatile char*)START_ADDRESS;
    for(int i = 0;i<MAX_ROWS * MAX_COLS * 2;i+=2){
        video[i]= ' ';
        video[i+1] = 0x00;
    } 
    cursor_x = 0;
    cursor_y = 0;
}

void print_char(char c, int colour) {
    int offset = 0;
    volatile char *video = (volatile char*)START_ADDRESS;
    if(c == '\n'){
        cursor_x = 0;
        cursor_y++;
    } else {
        offset = (cursor_y * 80 + cursor_x) * 2;
        video[offset] = c;
        video[offset+1] = colour;

        cursor_x++;

        if(cursor_x >= MAX_COLS){
            cursor_x = 0;
            cursor_y++;
        }
        if (cursor_y >= MAX_ROWS) {
            cursor_x = 0;
            cursor_y = 0; 
        }
    }
}

void print_string(const char* string, int kolor) {
    for(int i=0; string[i];i++) {
        print_char(string[i], kolor);
    }
}


void kernel_main(void) {
    clear_screen();
    print_string("Inicjalizacja IDT...\n", 0x07);
    idt_init();     
    
    print_string("Inicjalizacja Klawiatury...\n", 0x07);
    init_keyboard();

    print_string("Wlaczanie przerwan (STI)...\n", 0x07);
    __asm__ volatile ("sti");

    while(1) {
        __asm__ volatile ("hlt");
    }
}
