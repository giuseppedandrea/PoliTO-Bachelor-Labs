.model small
.stack
.data

matr3x3     dw 3,  0, -3
            dw 1,  4,  2
            dw 2, -1,  3
            
ris         dw ? 

.code
.startup

xor cx, cx  ; accumulatore

sub sp, 2
push matr3x3[6][2]
push matr3x3[6][4]
push matr3x3[12][2]
push matr3x3[12][4]
call matr2x2
pop ax
imul matr3x3[0][0] 
add cx, ax

sub sp, 2
push matr3x3[6][0]
push matr3x3[6][4]
push matr3x3[12][0]
push matr3x3[12][4]
call matr2x2
pop ax
imul matr3x3[0][2] 
sub cx, ax

sub sp, 2
push matr3x3[6][0]
push matr3x3[6][2]
push matr3x3[12][0]
push matr3x3[12][2]
call matr2x2
pop ax
imul matr3x3[0][4] 
add cx, ax

mov ris, cx

.exit

matr2x2 proc
        mov bp, sp
        push ax
        push bx
        mov ax, [bp+6]
        imul [bp+4]
        mov bx, ax
        mov ax, [bp+8]
        imul [bp+2]
        sub ax, bx
        mov [bp+10], ax
        pop bx
        pop ax
        ret 8
matr2x2 endp  

end