DIM EQU 8

.model small
.stack
.data

opo db 43
ris db ?

.code
.startup

mov al, opo
xor bx, bx
mov cx, DIM
ciclo: shr al, 1
       jnc next
       inc bl
       next:
       loop ciclo

mov ris, bl

.exit
end