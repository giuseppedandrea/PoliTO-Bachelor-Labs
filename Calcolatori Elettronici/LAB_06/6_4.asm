DIM EQU 5

.model small
.stack
.data

vet1    dw 2, 5, 1, 4, 6
vet2    dw 6, 3, 2, 7, 5

ris     dw DIM dup (?)

.code
.startup

xor di, di
mov cx, DIM
ciclo:  mov ax, vet1[di]
        mov bx, vet2[di]
        call media
        mov ris[di], ax
        add di, 2
        loop ciclo

.exit

media   proc
        add ax, bx
        sar ax, 1
        ret
media   endp    

end