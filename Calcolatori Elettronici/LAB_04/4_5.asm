.model small
.stack
.data

num dw 26  

rad dw ?

.code
.startup

mov ax, -1
mov dx, -1
mov cx, num
dec cx
ciclo: inc ax
       add dx, 2
       sub cx, dx
       cmp cx, 0
       jge ciclo

mov rad, ax

.exit
end