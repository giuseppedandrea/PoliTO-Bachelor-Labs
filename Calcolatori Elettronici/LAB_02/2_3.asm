DIM EQU 5
LF EQU 10
CR EQU 13
.model small
.stack
.data
message db 'Introdurre 5 interi positivi separati da ENTER: ', CR, LF
errore1 db 'ERRORE: Caratteri non numerici!                 ', CR, LF
errore2 db 'ERRORE: Intero troppo grande!                   ', CR, LF
vet dw DIM dup(?)
fattore dw 10
.code
.startup
mov ah, 2
mov cx, 50
lea di, message
stampa1: mov dl, [di]
         int 21h
         inc di
         loop stampa1

mov cx, DIM
lea di, vet
ciclo: mov di, 0
       lettura: mov ah, 1
                int 21h
                cmp al, CR
                jz fine_lettura
                cmp al, '0'
                jb err1
                cmp al, '9'
                ja err1
                mov ah, 0
                sub al, '0'            
                mov bx, ax
                mov ax, [di]
                mul fattore
                jc err2
                add ax, bx
                jc err2
                mov [di], ax            
                jmp lettura
        fine_lettura: add di, 2
        loop ciclo
jmp fine

err1: mov ah, 2
      mov cx, 50
      lea di, errore1 
      stampa2: mov dl, [di]
               int 21h
               inc di
               loop stampa2  
      jmp fine

err2: mov ah, 2
      mov cx, 50
      lea di, errore2 
      stampa3: mov dl, [di]
               int 21h
               inc di
               loop stampa3  
      jmp fine
    
fine:    
.exit
end