.model small
.stack
.data
var1 db 'a'
var2 db 's'
var3 db 'm'
.code
.startup
mov dh, 'A'-'a'
mov ah, 2
mov dl, var1
add dl, dh 
int 21h
mov dl, var2
add dl, dh
int 21h
mov dl, var3
add dl, dh
int 21h
.exit
end