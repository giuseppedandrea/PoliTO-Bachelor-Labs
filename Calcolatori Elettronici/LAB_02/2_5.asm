DIM EQU 20
.model small
.stack
.data

vet dw DIM dup(?)   

.code
.startup

lea di, vet

mov [di], 1
mov [di]+2, 1

mov cx, DIM-2
ciclo: mov ax, [di]
       add di, 2
       add ax, [di]
       mov [di]+2, ax
       loop ciclo

.exit
end