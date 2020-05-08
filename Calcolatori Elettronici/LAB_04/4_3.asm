DIM EQU 5

.model small
.stack
.data

;matrice dw 1, 0, 0, 0, 0
;        dw 0, 2, 0, 0, 0
;        dw 0, 0, 3, 0, 0
;        dw 0, 0, 0, 4, 0
;        dw 0, 0, 0, 0, 5

matrice dw 1, 4, 5, 6, 7
        dw 4, 2, 8, 6, 4
        dw 5, 8, 3, 2, 9
        dw 6, 6, 2, 4, 4
        dw 7, 4, 9, 4, 5

;matrice dw 1, 4, 5, 6, 7
;        dw 2, 2, 8, 6, 4
;        dw 5, 8, 3, 2, 9
;        dw 6, 6, 2, 4, 4
;        dw 7, 4, 9, 4, 5

.code
.startup

mov dl, 2
mov cx, 2 ; offset colonna
xor bx, bx ; spiazzamento riga
ciclo_1: mov di, cx ; spiazzamento colonna
         mov si, di
         add si, 2*(DIM-1)
         ciclo_2: mov ax, matrice[bx][di]
                  cmp ax, matrice[bx][si]
                  jnz nosimm
                  cmp ax, 0
                  jz next
                  mov dl, 1
                  next:
                  add si, 2*(DIM-1)+2
                  add di, 2
                  cmp di, 2*DIM
                  jl ciclo_2
         add cx, 2
         add bx, 2*DIM
         cmp bx, 2*(DIM-1)*(DIM-1)
         jl ciclo_1

jmp fine

nosimm:
mov dl, 0

fine:
add dl, '0'
mov ah, 2
int 21h         
         
.exit
end                  