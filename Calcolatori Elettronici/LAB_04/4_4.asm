DIM EQU 8

.model small 
.stack
.data

matrice db 0,  4,  0, 0,  0,  0,  0, 60
        db 0,  5,  0, 0, 11,  0,  0,  0
        db 0,  5,  7, 0,  0, 10,  0,  0
        db 0,  0,  0, 9,  0,  0, 49,  0
        db 0,  0, 10, 0,  0,  0,  0,  0
        db 0, 10,  3, 9,  0,  0, 12,  0
        db 0,  0, 58, 0,  0, 17,  0,  0
        db 0,  1,  0, 0,  3,  0,  0,  0

coord_x dw ?
coord_y dw ?
        
.code
.startup

xor dx, dx ; somma massima parziale
xor bx, bx ; indice colonna
ciclo_1: xor di, di ; indice riga
         ciclo_2: xor cx, cx ; accumulatore
                  xor ax, ax
                  
                  mov si, di
                  dec si
                  cmp si, 0
                  jl no_left
                  mov al, matrice[bx][si]
                  add cx, ax
                  no_left:         
                  mov si, di
                  inc si
                  cmp si, DIM-1
                  jg no_right
                  mov al, matrice[bx][si]
                  add cx, ax
                  no_right:
                  
                  mov si, bx
                  mov bx, di
                  mov di, si
                  
                  mov si, di
                  sub si, DIM
                  cmp si, 0
                  jl no_top
                  mov al, matrice[si][bx]
                  add cx, ax
                  no_top:
                  mov si, di
                  add si, DIM
                  cmp si, DIM*DIM-1
                  jg no_bottom
                  mov al, matrice[si][bx]
                  add cx, ax
                  no_bottom:
                  
                  mov si, bx
                  mov bx, di
                  mov di, si
                  
                  inc di
                  
                  cmp cx, dx
                  jle continue
                  mov dx, cx
                  mov coord_x, di
                  mov si, bx
                  mov ax, si
                  mov bl, DIM
                  div bl
                  inc ax
                  mov coord_y, ax
                  mov bx, si
                  
                  continue:
                  cmp di, DIM
                  jl ciclo_2
         add bx, DIM
         cmp bx, DIM*DIM
         jl ciclo_1


.exit
end