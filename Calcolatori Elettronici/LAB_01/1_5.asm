dim equ 7 
.model small
.stack
.data
vet dw 423, 3191, 23, 11, -412, 3, 9
.code
.startup
mov cx, dim/2
mov si, 0
mov di, (dim-1)*2
ciclo: mov ax, vet[si]
xchg vet[di], ax
mov vet[si], ax
add si, 2
sub di, 2
dec cx
cmp cx, 0
jnz ciclo
.exit
end