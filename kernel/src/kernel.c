#include "../include/kernel.h"
#include "../include/arch/idt.h"
#include "../include/drivers/keyboard.h"
#include "../include/drivers/screen.h"


//debug
//ctrl+alt+2
//xp /16bx 0x10000


void kernel_main(void) {
    idt_init();
    init_screen();
    init_keyboard();  

    print_string("Inicjalizacja IDT...\n", 0x07);
    print_string("Inicjalizacja Klawiatury...\n", 0x07);
    print_string("Wlaczanie przerwan...\n\n", 0x07);

    init_shell();
    
    __asm__ volatile ("sti");

    while(1) {
        __asm__ volatile ("hlt");
    }


}
