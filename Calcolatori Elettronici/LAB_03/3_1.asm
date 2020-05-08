DIM equ 4

.model small
.stack
.data

colonna dw 2, 5, 6, 7
riga    dw 7, 9, 2, 1

matrice dw DIM*DIM dup(?)

.code
.startup

mov cx, DIM
mov di, 0
mov bx, 0
ciclo1: push cx
        mov cx, DIM
        mov si, 0
        ciclo2: mov ax, colonna[di]
                mul riga[si]  
                jc overflow
                mov matrice[bx][si], ax
                add si, 2
                loop ciclo2
        pop cx
        add bx, DIM*2
        add di, 2
        loop ciclo1 
jmp fine
        
overflow: ; gestione overflow

fine:  

.exit
end