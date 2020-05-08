DIM EQU 4

.model small
.stack
.data

vett1 db 1, 2, 4, 5
vett2 db 3, 4, 1, 3

res db DIM dup (?)
par db 0

.code
.startup

xor bx, bx
ciclo: mov al, vett1[bx]
       and al, vett2[bx]
       jnp odd
       inc par
       odd:
       mov res[bx], al
       inc bx
       cmp bx, DIM
       jb ciclo
.exit
end