NUMCOL equ 6
NUMRIG equ 4

.model small
.stack
.data

tabella dw 154, 123,  109, 86,   4, ?
        dw 412, -23, -231,  9,  50, ?
        dw 123, -24,   12, 55, -45, ?
        dw NUMCOL dup(?)
           
.code
.startup

mov cx, NUMRIG-1
mov di, 0
ciclo1: push cx
        mov cx, NUMCOL-1
        mov bx, 0
        mov ax, 0
        ciclo1_1: add ax, tabella[di][bx]
                  jo overflow        
                  add bx, 2
                  loop ciclo1_1
        mov tabella[di][bx], ax
        add di, 2*NUMCOL
        pop cx
        loop ciclo1
mov cx, NUMCOL
mov di, 0
ciclo2: push cx
        mov cx, NUMRIG-1
        mov bx, 0
        mov ax, 0
        ciclo2_1: add ax, tabella[di][bx]
                  jo overflow        
                  add bx, 2*NUMCOL
                  loop ciclo2_1
        mov tabella[di][bx], ax
        add di, 2
        pop cx
        loop ciclo2
jmp fine

overflow: ; in caso di overflow

fine:

.exit
end