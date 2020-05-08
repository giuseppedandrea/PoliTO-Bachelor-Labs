DIM EQU 11

.model small
.stack
.data

stringa db 'nttte rossa'

new_dim dw ?

.code
.startup

lea ax, stringa
push ax
mov ax, DIM
push ax
sub sp, 2
call converti
pop ax
mov new_dim, ax
add sp, 4

.exit

converti    proc
            mov bp, sp
            push ax
            push bx
            push cx
            push dx
            push di
            push si
            mov cx, [bp+4]  ; dimensione stirnga
            mov di, [bp+6]  ; indirizzo stringa
            mov si, di
            inc si
            mov bx, 1
            ciclo:  mov al, [si]
                    cmp al, [di]
                    jz next
                    inc di 
                    mov [di], al
                    inc bx
                    next: inc si
                    loop ciclo
            mov [bp+2], bx
            pop si
            pop di
            pop dx
            pop cx
            pop bx
            pop ax
            ret
converti    endp


convertiBis proc
            mov bp, sp
            push ax
            push bx
            push cx
            push dx
            push di
            push si
            xor cx, cx      ; accumulatore valore di ritorno
            mov dx, [bp+4]  ; dimensione stirnga
            mov di, [bp+6]  ; indirizzo stringa
            mov si, di
            xor bx, bx
            ciclo1: mov al, [di][bx]
                    inc cx
                    inc si
                    ciclo2: inc bx
                            cmp bx, dx
                            jae fine_stringa
                            cmp al, [di][bx]
                            jz ciclo2
                    mov al, [di][bx]                    
                    mov [si], al
                    cmp bx, dx
                    jb ciclo1
            fine_stringa: mov [bp+2], cx
            pop si
            pop di
            pop dx
            pop cx
            pop bx
            pop ax
            ret
convertiBis endp

end