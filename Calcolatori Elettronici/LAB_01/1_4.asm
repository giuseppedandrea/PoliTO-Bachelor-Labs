.model small
.stack
.data
opa dw 32767
opb dw 1
.code
.startup
mov ax, opa
add ax, opb
add ax, opa
add ax, opb
.exit
end