.model small
.stack
.data
opa dw -459
opb dw 470
opc dw 32756
opd dw 1
.code
.startup
mov ax, opa
add ax, opb
add ax, opc
add ax, opd
.exit
end