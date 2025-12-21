BITS 16
ORG 0x7C00

msg db 'Hello world!', 0x0D, 0x0A, 0x0 ; 0x0D - carriage return, 0x0A -line feed
msg_disk_error db 'Boot Failure: Disk read error', 0x0D, 0x0A, 0x0 

mov ax, 0

;set segment registers
mov ds, ax
mov es, ax
mov fs, ax
mov gs, ax
mov ss, ax

mov sp, 0x7B00

mov si, msg ;hello world
call write_message

;disk
mov ax, 0x07E0
mov es, ax

mov ah, 2
mov al, 4
mov ch, 0
mov cl, 2
mov dh, 0

mov dl, 0x80 ;boot from hard drive

mov bx, 0x0000 ; es:bx

sti

int 0x13

jc disk_error 


jmp 0x07E0:0x0000

 
disk_error:
    mov si, msg_disk_error
    call write_message

jmp finish


write_message:
mov ah, 0xE
sti
next_char:
    lodsb ; DS:SI -> AL and SI++
    or al, al
    jz done
    int 0x10
    jmp next_char
done:
    cli
    ret

finish:

times 510-($-$$) db 0 
dw 0xAA55

