ENTRY(_start)
OUTPUT_FORMAT(binary)

SECTIONS
{
    . = 0x100000;

    .text : {
        kernel_entry.o(.text)
        *(.text)
    }

    .rodata : {
        *(.rodata)
    }

    .data : {
        *(.data)
    }

    .bss : {
        *(.bss)
        *(COMMON)
    }

    /DISCARD/ : {
        *(.eh_frame)
        *(.note.*)
        *(.comment)
    }
}