DIM equ 5
.model small
.stack
.data
vet db 5, 6, 8, 9, 5
risultato db ?
.code
.startup
mov cx, DIM
mov ah, 0
mov bx, 0
lea di, vet
ciclo: mov al, [di]
add bx, ax
jc errore
inc di
loop ciclo
mov cl, DIM
mov ax, bx
div cl
mov risultato, al
jmp fine
errore: 
fine: 
.exit
end