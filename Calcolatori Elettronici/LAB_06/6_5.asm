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
ciclo:  sub sp, 2   ; riservo spazio per il valore di ritorno
        push vet2[di]
        push vet1[di]
        call media
        add sp, 4
        pop ris[di]
        add di, 2
        loop ciclo

.exit

media   proc
        mov bp, sp
        push ax
        mov ax, [bp+2] 
        add ax, [bp+4]
        sar ax, 1
        mov [bp+6], ax
        pop ax
        ret
media   endp    

end