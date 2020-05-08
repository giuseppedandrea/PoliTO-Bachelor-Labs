DIM equ 10

.model small
.stack
.data
                     
tavola db DIM*DIM dup(?)

.code
.startup

mov cl, 1
mov di, 0
ciclo1: mov ch, 1
        mov bx, 0
        ciclo2: mov al, ch
                mul cl
                mov tavola[di][bx], al
                inc bx
                inc ch
                cmp ch, DIM
                jbe ciclo2
        add di, DIM
        inc cl
        cmp cl, DIM
        jbe ciclo1 

.exit
end