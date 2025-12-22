#include "../include/arch/ports.h"

unsigned char inb(uint16_t port) {
    unsigned char result;
    __asm__ volatile ("inb %w1, %b0" : "=a"(result) : "Nd"(port));
    return result;
}

unsigned short inw(uint16_t port) {
    unsigned short result;
    __asm__ volatile("inw %w1, %w0" : "=a"(result) : "Nd"(port));
    return result;
}

void outb(uint16_t port, uint8_t data) {
    __asm__ volatile("outb %b0, %w1" : : "a"(data), "Nd"(port));
}

void outw(uint16_t port, uint16_t data) {
    __asm__ volatile("outw %w0, %w1" : : "a"(data), "Nd"(port));
}