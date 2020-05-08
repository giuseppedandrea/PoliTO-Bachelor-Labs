.model small
.stack
.data
n1 db 10
n2 db 10h
n3 db 10b
res db ?
.code
.startup
mov al, n1
add al, n2
sub al, n3
mov res, al
.exit
end