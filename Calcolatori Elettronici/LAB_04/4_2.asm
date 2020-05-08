DIM EQU 8

.model small
.stack
.data

valore dw 1,    2,  5, 10, 20, 50, 100, 200
monete db 100, 23, 17,  0, 79, 48, 170, 211

euro dw ?
cent dw ?

.code
.startup

xor bx, bx ; parte bassa accumulatore
xor cx, cx ; parte alta accumulatore
xor di, di
xor si, si

ciclo: xor ax, ax
       mov al, monete[si] 
       mul valore[di]
       add bx, ax
       adc cx, dx
       jc overflow
       add di, 2
       inc si
       cmp si, DIM
       jl ciclo
       
mov ax, bx
mov dx, cx
mov bx, 100
div bx
mov euro, ax
mov cent, dx

jmp fine:

overflow: ; gestione overflow

fine:

.exit
end