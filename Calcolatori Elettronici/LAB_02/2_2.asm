.model small
.stack
.data
var dw 5988
.code
.startup
mov dx, 0       ; byte alto dividendo
mov ax, var     ; byte basso dividendo
mov bx, 10      ; divisore
mov cx, 0       ; contatore cifre
cifre: div bx
push dx         ; push in stack del resto
mov dx, 0       ; azzeramento byte alto dividendo
inc cx          ; incremento numero cifre
cmp ax, 0
jnz cifre
mov ah, 2
output: pop dx
add dx, '0'
int 21h
loop output
.exit
end