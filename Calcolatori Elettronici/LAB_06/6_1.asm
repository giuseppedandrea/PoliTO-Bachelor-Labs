LEN EQU 7

.model small
.stack
.data

stringa db 'esempio'

.code
.startup

lea si, stringa
xor ax, ax
mov cx, LEN
ciclo:  mov al, [si]
        call upper
        mov [si], al
        inc si
        loop ciclo


.exit

upper   proc
        sub al, 'a'
        add al, 'A'
        ret    
upper   endp

end