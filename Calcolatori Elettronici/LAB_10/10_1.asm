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
mov al, 10010010b
out dx, al

ciclo:  mov dx, PORTA
        in al, dx
        mov ah, al
        mov dx, PORTB
        in al, dx
        add al, ah
        jno no_overflow
        mov al, 0FFh
        no_overflow:
        mov dx, PORTC
        out dx, al
        
        mov cx, 5000 
        delay:  loop delay
        
        jmp ciclo
        
.exit
end
