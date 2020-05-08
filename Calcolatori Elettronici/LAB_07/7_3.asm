DIM EQU 4

.model small
.stack
.data

address dd 82C028D1h, 81C0276Ah, 4A7D276Ah, 0D5FE1150h
mask    dd 0FFFC0000h

.code
.startup

push 82C0h  ; parte alta indirizzo di riferimento
push 0B685h ; parte bassa indirizzo di riferimento
lea ax, address
push ax
lea ax, mask
push ax
sub sp, 2
call filtro
pop ax
add sp, 8

.exit

filtro proc
       mov bp, sp
       push ax
       push bx
       push cx
       push di
       push si
       mov di, [bp+6]   ; indirizzo address
       mov si, [bp+4]   ; indirizzo mask
       xor bx, bx       ; accumulatore valore di ritorno 
       mov cx, DIM
       ciclo:   mov ax, word ptr [di]   ; little endian -> parte bassa prima
                xor ax, [bp+8]          ; differenze tra rif e address
                and ax, word ptr [si]   ; solo i bit della mask
                jnz next
                mov ax, word ptr [di+2]
                xor ax, [bp+10]
                and ax, word prt [si+2]
                jnz next
                inc bx
                next:
                add di, 4
                loop ciclo
       mov [bp+2], bx
       pop si
       pop di
       pop cx
       pop bx
       pop ax          
       ret
filtro endp

end