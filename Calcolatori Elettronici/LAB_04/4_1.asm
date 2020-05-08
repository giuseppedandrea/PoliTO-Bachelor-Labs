LF		  EQU 10
CR		  EQU 13
LUNG_MESS EQU 33
.model small
.stack
.data

var_a dw 1
var_b dw 2
var_c dw 1

sol_mes		 db "Due soluzioni reali distinte   ", CR, LF  
sol_coin_mes db "Due soluzioni reali coincidenti", CR, LF
no_sol_mes   db "Non esistiono soluzioni reali  ", CR, LF 
overflow_mes db "Errore di overflow				", CR, LF

.code
.startup

mov ax, var_b
imul ax
jc overflow
push ax
mov ax, var_a
imul var_c
jc overflow
mov bx, 4
imul bx
jc overflow
pop bx
sub bx, ax
cmp bx, 0
jo overflow
js no_sol
jz sol_coin

lea si, sol_mes
jmp next

no_sol: lea si, no_sol_mes
		jmp next

sol_coin: lea si, sol_coin_mes
		  jmp next
		  

overflow: lea si, overflow_mes 

next: mov ah, 2
	  mov cx, LUNG_MESS
	  ciclo: mov dl, [si]
			 int 21h
			 inc si
			 loop ciclo 
	  mov ah, 2
	  mov cx, LUNG_MESS

.exit
end                                                     