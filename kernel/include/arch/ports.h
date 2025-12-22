#ifndef PORTS_H
#define PORTS_H

#include <stdint.h>

#include "ports.h"

unsigned char inb(uint16_t port);
unsigned short inw(uint16_t port);

void outb(uint16_t port, uint8_t data);
void outw(uint16_t port, uint16_t data);

#endif