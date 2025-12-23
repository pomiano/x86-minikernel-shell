#include "../include/drivers/keyboard.h"
#include "../include/arch/isr.h"
#include "../include/arch/ports.h"      
#include "../include/kernel.h"
#include "../include/shell.h"

typedef int bool;
#define true 1
#define false 0

static bool capslock_active = false;

const char ascii_low[] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\',
    'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' '
};

const char ascii_up[] = {
    0, 27, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')','_','+','\b',
    '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',
    0, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K','L',':','"','`' , 0, '|',
    'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0, '*', 0, ' '
};

char scancode_to_ascii(uint8_t scancode) {
    if(capslock_active == true)
        return ascii_up[scancode];
    else 
        return ascii_low[scancode];
}

static void keyboard_callback(registers_t regs) {
    uint8_t scancode = inb(0x60);
    if(scancode == 0xAA) {
        capslock_active = !capslock_active;
    }
    else if(scancode < 0x80) {
        if(scancode == 0x3A || scancode == 0x2A) {
            capslock_active = !capslock_active;
            return;
        }

        char c = scancode_to_ascii(scancode);
        if(c!=0){
            handle_keyboard_input(c);
        }
    }
}

void init_keyboard() {
    register_interrupt_handler(IRQ1, keyboard_callback); 
}