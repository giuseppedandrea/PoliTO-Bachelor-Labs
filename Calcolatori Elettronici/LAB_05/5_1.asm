LF EQU 10
CR EQU 13
LUNG_MESS EQU 25

.model small
.stack
.data

opa dw 2043
opb dw 5

res dw ?


mess_err db 'Inserito codice errato!', CR, LF

.code
.startup

mov ah, 1
int 21h
sub al, '0' ; offset ASCII
mov cl, al

mov ax, opa
mov bx, opb

cmp cl, 1
jz case_1
cmp cl, 2
jz case_2
cmp cl, 3
jz case_3
cmp cl, 4
jz case_4
jmp case_default

case_1: add ax, bx
        jc overflow
        jmp end_switch
case_2: sub ax, bx
        jc overflow
        jmp end_switch
case_3: mul bx
        jc overflow
        jmp end_switch
case_4: xor dx, dx
        div bx
        jmp end_switch
case_default: mov ah, 2
              xor bx, bx
              ciclo: mov dl, mess_err[bx]
                     int 21h
                     inc bx
                     cmp bx, LUNG_MESS
                     jnz ciclo
              jmp fine
    
end_switch:
mov res, ax
jmp fine

overflow: ; gestione overflow

fine:

.exit
end