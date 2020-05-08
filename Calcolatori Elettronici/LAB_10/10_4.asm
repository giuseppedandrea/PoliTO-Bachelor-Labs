DIM EQU 8

.model small
.stack
.data

vet1 db 00101101b, 01000010b, 01001011b, 10000001b, 01100011b, 11000000b, 11111111b, 00001011b 
vet2 dw DIM dup (?)

ris dw ?

.code
.startup

call extract
mov ris, di

.exit

extract proc
        push ax
        push cx
        push si
        xor si, si  ; indice vet1
        xor di, di  ; indice vet2
        mov cl, 4   ; usato per lo shift
        ciclo:  mov ah, vet1[si]
                inc si
                cmp si, DIM
                jae fine
                        
                mov al, vet1[si]
                mov bh, al
                shr ax, cl
                mov vet2[di], ax    
                add di, 2
                inc si
                cmp si, DIM
                jae fine
                
                and bh, 0Fh
                mov bl, vet1[si]
                mov vet2[di], bx
                add di, 2
                inc si
                cmp si, DIM
                jnz ciclo
        fine:
        shr di, 1
        pop si
        pop cx
        pop ax
        ret
extract endp

end