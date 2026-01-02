#include "../include/drivers/rtc.h"

uint8_t get_rtc_register(int reg){
    outb(0x70, reg);
    return inb(0x71);
}

void print_time(int colour) {
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

    day = (day & 0x0F) + ((day >> 4) * 10);
    month = (month & 0x0F) + ((month >> 4) * 10);
    year = (year & 0x0F) + ((year >> 4) * 10);

    //UTC != lokalny czas
    //zima w polsce utc+1
    //lato w polsce utc+2
    hour ++;
    hour = hour % 24;

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

    char yea[5];
    to_string(2000+year, yea);

    if(day<10)
        print_char('0', colour);
    print_string(d, colour);
    print_char('-', colour);
    if(month<10)
        print_char('0', colour);
    print_string(mon, colour);
    print_char('-', colour);
    print_string(yea, colour);
    print_string(" | ", colour);
    if(hour<10)
        print_char('0', colour);
    print_string(hou, colour);
    print_char(':', colour);
    if(min<10)
        print_char('0', colour);
    print_string(min, colour);
    print_char(':', colour);
    if(sec<10)
        print_char('0', colour);
    print_string(sec, colour);

}