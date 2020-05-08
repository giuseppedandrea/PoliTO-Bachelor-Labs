.model small
.stack
.data

opa db ?
opb db ?
ris db ?

.code
.startup

mov ah, 1

xor bx, bx  ; accumulatore
mov cx, 8   ; contatore
ciclo_a: int 21h
         sub al, '0'
         dec cx
         shl al, cl
         or bl, al
         cmp cx, 0
         jnz ciclo_a
mov opa, bl
int 21h  
xor bx, bx  ; accumulatore
mov cx, 8   ; contatore
ciclo_b: int 21h
         sub al, '0'
         dec cx
         shl al, cl
         or bl, al
         cmp cx, 0
         jnz ciclo_b
mov opb, bl


mov al, opb
not al
and al, opa
not al
mov ah, opa
xor ah, opb
or ah, al
mov ris, ah


.exit
end