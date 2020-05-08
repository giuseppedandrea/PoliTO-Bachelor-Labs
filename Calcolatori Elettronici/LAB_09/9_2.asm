PORTA   EQU 80h
PORTB   EQU PORTA+1
PORTC   EQU PORTA+2
CONTROL EQU PORTA+3


#start=8255.exe#
.model small
.stack
.data
.code
.startup

mov dx, CONTROL
mov al, 10000000b
out dx, al
mov cx, 255
ciclo:  mov al, cl
        test cl, 1
        jz pari
        mov dx, PORTA
        jmp next
        pari:
        mov dx, PORTB
        next:
        out dx, al
        dec cx
        cmp cx, 0
        jns ciclo
        
.exit
end