PORTA   EQU 80h
PORTB   EQU PORTA+1
PORTC   EQU PORTA+2
CONTROL EQU PORTA+3

#START=8255.exe#
.model small
.stack
.data

lettura db ?

.code
.startup

mov dx, CONTROL
mov al, 10001001b
out dx, al
mov dx, PORTA
mov al, 'O'
out dx, al
mov dx, PORTB
mov al, 'K'
out dx, al
mov dx, PORTC
in al, dx
mov lettura, al

.exit
end
