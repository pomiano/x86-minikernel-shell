BITS 16
ORG 0x7E00

;wlaczenie A20
;przejscie do protected mode
    ;wylaczyc cli
    ;ustawienie gtd
    ;ustawienie bitu PE w rejestrze CR0
;uruchomienie kernela - skok do tego adresu

cli

;check A20
check:

mov si, 0x7E00
mov es, si
mov gs, si

mov si, 0
mov di, 0x10000

mov ah, byte [es:si]
push ax

mov ah, byte [gs:si]
push ax

mov byte [es:si], 0x01
mov byte [gs:di], 0x0A

cmp [gs:di], 0x01

pop ax
mov byte [gs:si], ah

pop ax
mov bye [es:si], ah
jnz A20_active

activate_A20:


call a20wait_write
mov al, 0xAD 
out 0x64, al ;keyboard off

mov al, 0xD0
out 0x64, al 

in al, 0x60  ; Read Controller Output Port 

or al, 0x02  ; activate A20
mov bl,al 

mov al, 0xD1
out 0x64, al

mov al, bl
out 0x60, al

mov al, 0xAE
out 0x64, al ;keyboard on

jmp A20_active

a20wait_write:
    in al, 0x64  
    test al, 0x02  
    jnz a20wait_write
    ret

a20wait_read:
    in al, 0x64  
    test al, 0x01 
    jnz a20wait_read
    ret

A20_active:

sti


write_message:
next_char:
    lodsb ; DS:SI -> AL and SI++
    or al, al
    jz done
    int 0x10
    jmp next_char
done: