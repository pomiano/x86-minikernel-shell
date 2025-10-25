BITS 16
ORG 0x7E00

;wlaczenie A20
;przejscie do protected mode
    ;wylaczyc cli
    ;ustawienie gtd
    ;ustawienie bitu PE w rejestrze CR0
;uruchomienie kernela - skok do tego adresu

;set segment registers
mov ds, 0
mov es, 0
mov fs, 0
mov gs, 0
mov ss, 0