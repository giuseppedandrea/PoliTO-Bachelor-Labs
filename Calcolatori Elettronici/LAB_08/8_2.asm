DIM EQU 6

.model small
.stack
.data

anni        dw 1945, 2008, 1800, 2006, 1748, 1600
risultato   db DIM dup (0)

.code
.startup

lea si, anni
lea di, risultato
mov bx, DIM
call anni_bisestili

.exit

anni_bisestili  proc
                push ax
                push bx
                push cx
                push dx
                push di
                push si
                mov cx, bx
                ciclo:  mov dx, [si]    ; anno
                        mov ax, dx
                        mov bl, 100
                        div bl
                        cmp ah, 0
                        jnz no_secolare
                        mov ax, dx
                        xor dx, dx
                        mov bx, 400
                        div bx
                        cmp dx, 0
                        jnz next
                        inc [di]
                        jmp next
                        no_secolare:
                        test dx, 3
                        jnz next
                        inc [di]
                        next:
                        add si, 2
                        inc di
                        loop ciclo
                pop si
                pop di
                pop dx
                pop cx
                pop bx
                pop ax                         
                ret
anni_bisestili  endp

end