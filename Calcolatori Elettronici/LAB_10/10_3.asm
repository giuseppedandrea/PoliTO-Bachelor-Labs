PORTA   EQU 80h
PORTB   EQU PORTA+1
PORTC   EQU PORTA+2
CONTROL EQU PORTA+3  

DIM EQU 3

#start=8255.exe#
.model small
.stack
.data

vet_pari dw DIM dup (?)
vet_disp dw DIM dup (?)
ind_pari db 0
ind_disp db 0

flag db 0
temp db 0

.code
.startup

mov dx, CONTROL
mov al, 10010000b
out dx, al

ciclo:  call lettura
        jmp ciclo

.exit

lettura proc
        push ax
        push bx
        push dx
    
        mov dx, PORTA
        in al, dx
        test flag, 1
        jz next
        xor bx, bx
        mov ah, temp
        test ax, 1
        jnz disp
        
        pari:   cmp ind_pari, DIM
                jb next_pari
                mov ind_pari, 0
                next_pari:
                mov bl, ind_pari    ; indice vettore
                shl bx, 1   ; moltiplicazione per due 
                mov vet_pari[bx], ax
                inc ind_pari
                mov flag, 0
                jmp fine
        disp:   cmp ind_disp, DIM
                jb next_disp
                mov ind_disp, 0
                next_disp:
                mov bl, ind_disp
                shl bx, 1
                mov vet_disp[bx], ax
                inc ind_disp
                mov flag, 0
                jmp fine
        
        
        next:   mov flag, 1
                mov temp, al 
        
        fine:
        pop dx
        pop bx
        pop ax        
        ret
lettura endp    

end