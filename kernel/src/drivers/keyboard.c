#include "../include/drivers/keyboard.h"
#include "../include/arch/isr.h"
#include "../include/arch/ports.h"      
#include "../include/kernel.h"

const char ascii_tab[] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\',
    'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' '
};

char scancode_to_ascii(uint8_t scancode) {
    return ascii_tab[scancode];
}

static void keyboard_callback(registers_t regs) {
    uint8_t scancode = inb(0x60);
    if(scancode < 0x80) {
        char c = scancode_to_ascii(scancode);
        if(c!=0){
            print_char(c, 0x07);    
        }
    }
}

void init_keyboard() {
    register_interrupt_handler(IRQ1, keyboard_callback); 
}