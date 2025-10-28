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

; cli

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

times 2048 - ($ - $$) db 0