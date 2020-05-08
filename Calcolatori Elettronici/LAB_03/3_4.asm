DIM equ 4

.model small
.stack
.data

vettore   db -5, -45, -96, -128
addendo   dd 69000
risultato dd ?

.code
.startup

mov cx, DIM
mov bx, 0
lea di, vettore
ciclo: mov al, [di]
       cbw
       add bx, ax
       inc di
       loop ciclo
mov ax, bx
cwd
       
add ax, word ptr addendo
adc dx, word ptr addendo+2 

mov word ptr risultato, ax
mov word ptr risultato+2, dx

.exit
end