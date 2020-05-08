DIM EQU 4

.model small
.stack
.data

numeri    db 2, 19, 17, 45
risultato db DIM dup (?) 

.code
.startup

xor bx, bx
ciclo1: mov ch, numeri[bx] ; divisore
        mov cl, ch
        dec cl
        mov risultato[bx], 0
        ciclo2: xor ax, ax
                mov al, ch
                div cl
                cmp ah, 0
                jz next
                dec cl
                cmp cl, 1
                ja ciclo2 
        mov risultato[bx], 1                     
        next:
        inc bx
        cmp bx, DIM
        jb ciclo1

.exit
end