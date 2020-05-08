DIM EQU 5

.model small
.stack
.data

prezzi      dw 39, 1880, 2394, 1000, 1590
scontati    dw DIM dup (?)
sconto      dw 30
totsconto   dw 0

.code
.startup

call calcolo_sconto

.exit

calcolo_sconto  proc
                push ax
                push bx
                push cx
                push dx
                push di
                xor di, di
                mov cx, DIM
                ciclo:  mov ax, prezzi[di]
                        mov bx, 100
                        sub bx, sconto
                        mul bx
                        mov bx, 100
                        div bx
                        cmp dx, 50
                        jb next
                        inc ax
                        next:
                        mov scontati[di], ax
                        mov dx, prezzi[di]
                        sub dx, ax
                        add totsconto, dx 
                        add di, 2
                        loop ciclo
                pop di
                pop dx
                pop cx
                pop bx
                pop ax
                ret
calcolo_sconto  endp

end