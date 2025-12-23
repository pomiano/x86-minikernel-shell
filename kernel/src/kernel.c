#include "../include/kernel.h"
#include "../include/arch/idt.h"
#include "../include/drivers/keyboard.h"
#include "../include/drivers/screen.h"


//ctrl+alt+2
//xp /16bx 0x10000



void kernel_main(void) {
    clear_screen();
    print_string("Inicjalizacja IDT...\n", 0x07);
    idt_init();     
    
    print_string("Inicjalizacja Klawiatury...\n", 0x07);
    init_keyboard();

    print_string("Wlaczanie przerwan (STI)...\n", 0x07);
    __asm__ volatile ("sti");
    print_string("WITAJ W milOS!!\n", 0x07);
  


    while(1) {
        __asm__ volatile ("hlt");
    }
}
