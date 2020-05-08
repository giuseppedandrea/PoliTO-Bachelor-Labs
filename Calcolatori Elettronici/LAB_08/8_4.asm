.model small
.stack
.data

risultato dd ?

.code
.startup

mov ax, 3
mov bx, 12
push ax ; base
push bx ; esponente
sub sp, 4
call potenza
pop ax
pop dx
add sp, 4
mov risultato, ax
mov risultato+2, dx

.exit

potenza proc 
        mov bp, sp
        push ax
        push bx
        push cx
        push dx
                
        mov ax, 1   ; accumulatore doubleword ax:dx
        mov dx, 0   ; inizialmente a 1 (ax meno significativo)
        mov cx, [bp+6]  ; esponente
        cmp cx, 0
        jz uno        
        
        ciclo:  mov bx, dx
                mul word ptr [bp+8]
                push ax ; parte meno significativa (ok)
                push dx ; resto parte piu' significativa
                mov ax, bx
                mul word ptr [bp+8]
                jc overflow2
                pop dx
                add dx, ax
                jc overflow1
                pop ax                
                loop ciclo
        mov [bp+2], ax
        mov [bp+4], dx
        jmp fine
        
        uno:    mov [bp+2], 1
                mov [bp+4], 0
                jmp fine
            
        overflow2:  add sp, 2
        overflow1:  add sp, 2
                    mov [bp+2], 0FFFFh
                    mov [bp+4], 0FFFFh
        
        fine:
        pop dx
        pop cx
        pop bx
        pop ax
        ret
potenza endp

end