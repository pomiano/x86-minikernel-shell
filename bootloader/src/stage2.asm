BITS 16
ORG 0x7E00


mov si, msg 
call write_message


;wlaczenie A20
;przejscie do protected mode
    ;wylaczyc cli
    ;ustawienie gtd
    ;ustawienie bitu PE w rejestrze CR0
;uruchomienie kernela - skok do tego adresu

cli

;check A20
check:

xor ax, ax
mov es, ax          ; ES = 0x0000 -> adres 0x00000
mov si, 0

mov ax, 0xFFFF
mov gs, ax          ; GS = 0xFFFF -> adres 0xFFFF0
mov di, 0x0010      ; +0x10 = 0x100000

mov ah, byte [es:si]
push ax

mov ah, byte [gs:si]
push ax

mov byte [es:si], 0x01
mov byte [gs:di], 0x0A

cmp byte [gs:di], 0x01

pop ax
mov byte [gs:si], ah

pop ax
mov byte [es:si], ah
jnz A20_active


mov si, msg_A20_notactive
call write_message

jmp finish

; activate_A20:


; call a20wait_write
; mov al, 0xAD 
; out 0x64, al ;keyboard off

; mov al, 0xD0
; out 0x64, al 

; in al, 0x60  ; Read Controller Output Port 

; or al, 0x02  ; activate A20
; mov bl,al 

; mov al, 0xD1
; out 0x64, al

; mov al, bl
; out 0x60, al

; mov al, 0xAE
; out 0x64, al ;keyboard on

; jmp A20_active

; a20wait_write:
;     in al, 0x64  
;     test al, 0x02  
;     jnz a20wait_write
;     ret

; a20wait_read:
;     in al, 0x64  
;     test al, 0x01 
;     jnz a20wait_read
;     ret

A20_active:

mov si, msg_A20_active
call write_message

jmp finish

msg db 'Hello stage 2!', 0x0D, 0x0A, 0x0; 0x0D - carriage return, 0x0A -line feed
msg_A20_active db 'A20 is active!', 0x0D, 0x0A, 0x0
msg_A20_notactive db 'A20 is not active!', 0x0D, 0x0A, 0x0



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


tss32_start:
    dw 0 , 0 ;link , reserved
    dd 0 ; ESP0
    dw 0 , 0 ;SS0 , reserved
    dd 0 ; ESP1
    dw 0 , 0 ;SS1 , reserved
    dd 0 ; ESP2
    dw 0 , 0 ;SS2 , reserved
    dd 0 ; CR3
    dd 0,0 ; EIP,EFLAGS
    dd 0,0,0,0,0,0,0,0 ;EAX,ECX,EDX,EBX,ESP,EBP,ESI,EDI
    dw 0 , 0 ; ES,reserved
    dw 0 , 0 ; CS,reserved
    dw 0 , 0 ; SS,reserved
    dw 0 , 0 ; DS,reserved
    dw 0 , 0 ; FS,reserved
    dw 0 , 0 ; GS,reserved
    dw 0 , 0 ; LDTR, reserved
    dw 0 ,0 ; reserved, IOPB
    dd 0 ; SSP(shadow stack pointer)

tss32_end:
 

gdt_start:                                                                                                                          

gdt_null:  dq 0 


gdt_kernel_code:
    dw 0xFFFF ;limit 0-15
    dw 0x0 ;base 0-15
    db 0x0 ;base 16-23
    db 0x9A ;access byte 0-7
    db 0xCF ;flags and limit 16-19
    db 0x0 ;base 24-31

gdt_kenel_data:
    dw 0xFFFF ;limit 0-15
    dw 0x0 ;base 0-15
    db 0x0 ;base 16-23
    db 0x92 ;access byte 0-7
    db 0xCF ;flags and limit 16-19
    db 0x0 ;base 24-31

gdt_user_code:
    dw 0xFFFF ;limit 0-15
    dw 0x0 ;base 0-15
    db 0x0 ;base 16-23
    db 0xFA ;access byte 0-7
    db 0xCF ;flags and limit 16-19
    db 0x0 ;base 24-31

gdt_user_data:
    dw 0xFFFF ;limit 0-15
    dw 0x0 ;base 0-15
    db 0x0 ;base 16-23
    db 0xF2 ;access byte 0-7
    db 0xCF ;flags and limit 16-19
    db 0x0 ;base 24-31

gdt_tss:
    li12 dw 0xFFFF ;limit 0-15
    bs12 dw 0x0 ;base 0-15
    bs3 db 0x0 ;base 16-23
    db 0x89  ;access byte 0-7
    db 0xCF ;flags and limit 16-19
    bs4 db 0x0 ;base 24-31

gdt_end:

;base
mov ax, ds
shl ax, 4
add ax, tss32_start

mov bs12, ax ;base 0-15

;limit
mov ax, tss32_end-tss32_start-1
mov li12, ax

gdtr:
    dw gdt_end - gdt_start - 1 ;limit
    dd gdt ;base

lgdt [gdtr] ;trzeba uporzadkowac


times 2048 - ($ - $$) db 0