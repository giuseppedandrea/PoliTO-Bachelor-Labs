.model small
.stack
.data

n db 6
k db 3

risultato dw ?

.code
.startup

call combina

.exit

combina proc
        push ax
        push bx
        push cx
        push dx
        xor ah, ah
        mov al, n
        xor bh, bh
        mov bl, al
        xor ch, ch
        mov cl, k
        dec cl
        ciclo1: dec bl
                mul bx   
                loop ciclo1
        mov bl, k
        mov cl, bl
        dec cx
        ciclo2: div bl
                dec bl
                loop ciclo2
        mov risultato, ax
        pop dx
        pop cx
        pop bx
        pop ax
        ret
combina endp

end