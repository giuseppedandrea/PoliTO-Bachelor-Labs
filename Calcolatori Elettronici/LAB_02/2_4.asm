.model small
.stack
.data

giorni db 45
ore    db 12
minuti db 40

risultato dw ?

.code
.startup

mov al, 24
mul giorni


mov bl, ore
mov bh, 0
add ax, bx

mov bx, 60
mul bx
jc overflow

mov bl, minuti
mov bh, 0
add ax, bx
jc overflow

mov risultato, ax

jmp fine

overflow: mov risultato, 0FFFFh

fine:

.exit
end