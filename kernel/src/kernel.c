#include "kernel.h"

//ctrl+alt+2
//xp /16bx 0x10000

void kernel_main(void) {
    // Adres pamięci wideo VGA (lewy górny róg)
    volatile char* vga = (volatile char*)0xB8000;
    
    // Wypisujemy 'X' na czerwonym tle, żeby było widać z daleka
    vga[0] = 'E';    // Znak
    vga[1] = 0x4F;   // Kolor (4 = czerwony, F = biały tekst)

    while(1) {
        // Zatrzymujemy procesor
    }
}
