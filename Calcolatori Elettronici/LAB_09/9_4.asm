PORTA   EQU 80h
PORTB   EQU PORTA+1
PORTC   EQU PORTA+2
CONTROL EQU PORTA+3


#start=8255.exe#
.model small
.stack
.data

a   db ?
b   db ?
ris db ?

.code
.startup

mov dx, CONTROL
mov al, 10010010b
out dx, al
mov dx, PORTA
in al, dx
mov a, al
mov dx, PORTB
in al, dx
mov b, al
xor al, a
not al
mov ris, al
mov ah, al
mov dx, CONTROL
mov cx, 7
ciclo:  mov al, cl
        shl al, 1
        shl ah, 1
        adc al, 0
        out dx, al
        dec cx
        jns ciclo
        
.exit
end