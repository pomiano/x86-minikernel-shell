#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "arch/isr.h"

#define KEY_UP -1
#define KEY_DOWN -2
#define KEY_LEFT -3
#define KEY_RIGHT -4

char scancode_to_ascii(uint8_t scancode);
void init_keyboard();
static void keyboard_callback(registers_t regs);

#endif