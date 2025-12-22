#include "../include/arch/idt.h"
#include "../include/arch/isr.h"

struct IDTR {
    uint16_t limit; 
    uint32_t base;
} __attribute__((packed));

struct InterruptDescriptor32 {
   uint16_t offset_1;        // offset bits 0..15
   uint16_t selector;        // a code segment selector in GDT or LDT
   uint8_t  zero;            // unused, set to 0
   uint8_t  type_attributes; // gate type, dpl, and p fields
   uint16_t offset_2;        // offset bits 16..31
} __attribute__((packed)); //zeby scisnac zmienne kolo siebie w pamieci


struct IDTR idtr;
struct InterruptDescriptor32 idt[256];

void set_idt_gate(int num, uint32_t handler, uint16_t sel, uint8_t flags){
   idt[num].offset_1 = handler & 0xFFFF;       
   idt[num].selector = sel;
   idt[num].zero = 0;
   idt[num].type_attributes = flags;
   idt[num].offset_2 = (handler >> 16) & 0xFFFF; 
}

extern void irq1();
extern void irq0();

void pic_remap() {
    outb(0x20, 0x11); // master PIC
    outb(0xA0, 0x11); // slave PIC

    outb(0x21, 0x20); 
    outb(0xA1, 0x28); 

    outb(0x21, 0x04); // slave jest wpiety do irq2 czyli  100b = 4 
    outb(0xA1, 0x02); // slave jest wpiety po prostu do irq2 czyli 10 = 2

    outb(0x21, 0x01);
    outb(0xA1, 0x01);

    outb(0x21, 0x00);
    outb(0xA1, 0x00);
}

void idt_init(void) {
   idtr.base = (uint32_t)&idt;
   idtr.limit = (sizeof(struct InterruptDescriptor32) * 256) - 1;

   set_idt_gate(32, (uint32_t)irq0, 0x08, 0x8E);
   set_idt_gate(33, (uint32_t)irq1, 0x08, 0x8E);

   __asm__ volatile ("lidt %0" : : "m"(idtr)); // __asm__ mowi kompilatorowi ze ma to przekazac do assemblera
   // volatile zeby nie zmienial nic, w nawiasie jest funckja, %0 czyli argumenty, "m"

   pic_remap();
}