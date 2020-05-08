LEN EQU 7

.model small
.stack
.data

stringa db "esempio"

.code
.startup

lea ax, stringa
mov bx, LEN
call print


.exit

print   proc
        push ax
        push bx
        push cx
        push di
        mov di, ax
        mov cx, bx
        mov ah, 2
        ciclo:  mov dl, [di]
                int 21h
                inc di                    
                loop ciclo    
        pop di
        pop cx
        pop bx
        pop ax
        ret    
print   endp    

end

