#ifndef RTC_H
#define RTC_H

#include "../include/arch/ports.h"
#include <stdint.h>
#include "../include/drivers/screen.h"
#include "../include/lib/string.h"

uint8_t get_rtc_register(int reg);
void print_time();


#endif