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
mov al, 10010000b
out dx, al

mov dx, PORTC
mov al, 10011100b
out dx, al ; valore di prova

call rdwr 

.exit

rdwr    proc
        mov dx, PORTA
        in al, dx
        mov cl, al
        mov bl, 1
        shl bl, cl
        mov dx, PORTC
        in al, dx
        xor al, bl
        out dx, al        
        ret
rdwr    endp

end