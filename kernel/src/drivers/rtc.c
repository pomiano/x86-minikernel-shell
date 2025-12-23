#include "../include/drivers/rtc.h"

uint8_t get_rtc_register(int reg){
    outb(0x70, reg);
    return inb(0x71);
}

void print_time() {
    //podane wartosci sa w hex, ale decymalnie czyli 0x35 oznacza 35 min
    uint8_t second = get_rtc_register(0x00);
    uint8_t minute = get_rtc_register(0x02);
    uint8_t hour   = get_rtc_register(0x04);
    uint8_t day = get_rtc_register(0x07);
    uint8_t month = get_rtc_register(0x08);
    uint8_t year   = get_rtc_register(0x09);

    second = (second & 0x0F) + ((second >> 4) * 10);
    minute = (minute & 0x0F) + ((minute >> 4) * 10);
    hour = (hour & 0x0F) + ((hour >> 4) * 10);

    day = day * 10;
    month = month * 10;
    year = (year & 0x0F) + ((year >> 4) * 10);

    char sec[3];
    to_string(second, sec);

    char min[3];
    to_string(minute, min);

    char hou[3];
    to_string(hour,hou);

    char d[3];
    to_string(day, d);

    char mon[3];
    to_string(month, mon);

    char yea[3];
    to_string(2000+year, yea);

    print_string(d, 0x0F);
    print_char('-', 0x0F);
    print_string(mon, 0x0F);
    print_char('-', 0x0F);
    print_string(yea, 0x0F);
    print_string("   ", 0x0F);
    print_string(hou, 0x0F);
    print_char(':', 0x0F);
    print_string(min, 0x0F);
    print_char(':', 0x0F);
    print_string(sec, 0x0F);

}