#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "arch/isr.h"

char scancode_to_ascii(uint8_t scancode);
void init_keyboard();
static void keyboard_callback(registers_t regs);

#endif