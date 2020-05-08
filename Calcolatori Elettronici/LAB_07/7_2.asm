LUNG_MESS EQU 30 
CR EQU 13
LF EQU 10


.model small
.stack
.data

mess_ins    db "Numero intero e ENTER:      ", CR, LF
mess_even   db "Il numero inserito e' pari  ", CR, LF
mess_odd    db "Il numero inserito e'dispari", CR, LF
mess_err    db "Numero inserito non valido  ", CR, LF

.code
.startup

lea ax, mess_ins
mov bx, LUNG_MESS
call stampa
xor bx, bx  ; numero cifre acquisite
mov ah, 1
lettura:    mov dl, al
            int 21h 
            cmp al, CR
            jz next
            cmp al, '0'
            jl errore
            cmp al, '9'
            jg errore
            inc bx
            jmp lettura
            
next:       cmp bx, 0
            jz errore
            sub dl, '0'
            test dl, 1
            jz pari 
            jmp dispari


pari:       lea ax, mess_even
            mov bx, LUNG_MESS
            call stampa
            jmp fine
        
dispari:    lea ax, mess_odd
            mov bx, LUNG_MESS
            call stampa
            jmp fine

errore:     lea ax, mess_err
            mov bx, LUNG_MESS
            call stampa
            jmp fine
            
fine:

.exit

; Parametri:
; ax -> indirizzo iniziale della stringa
; bx -> lunghezza della stringa
stampa proc
       push ax
       push bx
       push dx
       push di  
       lea di, ax
       mov ah, 2
       ciclo:   mov dl, [di]
                int 21h
                inc di
                dec bx
                cmp bx, 0
                jnz ciclo
       pop ax
       pop bx
       pop dx
       pop di   
       ret
stampa endp


end