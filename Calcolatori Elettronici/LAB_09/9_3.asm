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
mov al, 10011001b
out dx, al
mov dx, PORTC
xor ah, ah  ; valore precedente (inizialmente 0)
ciclo:  in al, dx
        test ah, 1
        jnz next    ; salto se ultimo bit precedente a 1  
        test al, 1
        jz next     ; salto se ultimo bit attuale a 0
        call converti        
        next:
        mov ah, al
        jmp ciclo
        
.exit

converti    proc
            push ax
            push dx
            mov dx, PORTA
            in al, dx
            cmp al, 'a'
            jl fine
            cmp al, 'z'
            jg fine
            mov dx, PORTB
            sub al, 'a'
            add al, 'A'
            out dx, al            
            fine:
            pop dx
            pop ax            
            ret
converti    endp

end