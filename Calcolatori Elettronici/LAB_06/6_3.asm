DIM EQU 5

.model small
.stack
.data

vet1    dw 2, 5, 1, 4, 6
vet2    dw 6, 3, 2, 7, 5

ris     dw DIM dup (?)

el1     dw ?        
el2     dw ?
med     dw ?

.code
.startup

xor di, di
mov cx, DIM
ciclo:  mov ax, vet1[di]
        mov el1, ax
        mov ax, vet2[di]
        mov el2, ax
        call media
        mov ax, med
        mov ris[di], ax
        add di, 2
        loop ciclo

.exit

media   proc
        push ax
        mov ax, el1
        add ax, el2
        sar ax, 1
        mov med, ax
        pop ax            
        ret
media   endp    

end