DIM EQU 11
CR EQU 13
LF EQU 10

.model small
.stack
.data

stringa db 'sasso rosso'

freq db 26 DUP (0)

.code
.startup

xor bx, bx
lea di, stringa
mov cx, DIM
ciclo1: mov bl, [di]
        cmp bl, 'a'
        jl next
        cmp bl, 'z'
        jg next
        sub bl, 'a'
        inc freq[bx]
        next:
        inc di
        loop ciclo1  

xor di, di
mov cx, 26
ciclo2: call stampa_isto
        inc di
        loop ciclo2
        
.exit

; Parametri:
; di: indice freq
stampa_isto proc
            push ax
            push cx
            push dx
            xor cx, cx
            mov cl, freq[di]
            cmp cx, 0
            jz no_star
            mov ah, 2
            mov dx, 'a'
            add dx, di
            int 21h
            mov dl, ' '
            int 21h
            mov dl, '*'
            star:   int 21h
                    loop star 
            mov dl, CR
            int 21h
            mov dl, LF
            int 21h       
            no_star:
            pop dx
            pop cx
            pop ax
            ret
stampa_isto endp

end