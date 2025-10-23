;https://wiki.osdev.org/Real_mode_assembly_I and https://www.ctyme.com/intr/rb-0106.htm and chat.gpt
BITS 16
ORG 0x7C00

msg db 'Hello world!', 0x0D, 0x0A, 0x0 ; 0x0D - carriage return, 0x0A -line feed

mov ax, 0
mov ds, ax
mov es, ax
mov ss, ax
mov sp, 0x7000

mov si, msg
mov ah, 0xE

next_char:
    lodsb ; DS:SI -> AL and SI++
    or al, al
    jz done
    int 0x10
    jmp next_char
done:
    cli
hang:
    hlt
    jmp hang
  


mov ah, 2
mov al, 1
mov ch, 0
mov cl, 2
mov dh, 0

mov es, 0x7E00
mov bx, 0x0000 ; es:bx

int 0x13

;todo sprawdzenie sukcesu
jmp 0x07E0:0x00

 

times 510-($-$$) db 0 
dw 0xAA55

