.586
.model flat, stdcall
includelib libucrt.lib
includelib kernel32.lib

includelib "D:\User\Desktop\CourseWork\SYO-2020\Generation\Debug\GenLib.lib
ExitProcess PROTO:DWORD 
.stack 4096

 outnum PROTO : DWORD

 outstr PROTO : DWORD

 sqroot PROTO : DWORD

 module PROTO : DWORD

 input PROTO : DWORD

.const
		printline byte 13, 10, 0
		L1 sdword 1
		L2 byte ' ', 0
		L3 sdword 2
		L4 byte 'Введите число нижний предел: ', 0
		L5 byte 'Введите число верхний предел: ', 0
		L6 sdword 100
		L7 byte 'Результат после вычисления выражения: ', 0
		L8 sdword 125
		L9 byte 'Модуль результата: ', 0
		L10 byte 'Квадратный корень результата: ', 0
		L11 byte 'Остаток от деления на 2 результата квадратного корня: ', 0
.data
		temp sdword ?
		buffer byte 256 dup(0)
		oddi sdword 0
		maxres sdword 0
		maina sdword 0
		mainb sdword 0
		maink sdword 0
		mainc sdword 0
.code

;----------- odd ------------
odd PROC,
	oddt : sdword, oddn : sdword  
push ebx
push edx

mov edx, oddt
cmp edx, oddn

jl repeat1
jmp repeatnext1
repeat1:
push oddi
push L1
pop ebx
pop eax
add eax, ebx
push eax

pop ebx
mov oddi, ebx


push oddt
call outnum



push offset L2
call outstr


push oddt
push L3
pop ebx
pop eax
add eax, ebx
push eax

pop ebx
mov oddt, ebx

mov edx, oddt
cmp edx, oddn

jl repeat1
repeatnext1:

pop edx
pop ebx
mov eax, oddi
ret
odd ENDP
;------------------------------


;----------- max ------------
max PROC,
	maxa : sdword, maxb : sdword  
push ebx
push edx

mov edx, maxa
cmp edx, maxb

jg right2
jl wrong2
right2:
push maxa

pop ebx
mov maxres, ebx

jmp next2
wrong2:
push maxb

pop ebx
mov maxres, ebx

next2:

pop edx
pop ebx
mov eax, maxres
ret
max ENDP
;------------------------------


;----------- MAIN ------------
main PROC

push offset L4
call outstr



push maina
call input
push eax

pop ebx
mov maina, ebx


push offset L5
call outstr



push mainb
call input
push eax

pop ebx
mov mainb, ebx


push mainb
push maina
call odd
push eax

pop ebx
mov mainb, ebx


push mainb
push maina
call max
push eax

pop ebx
mov maink, ebx

push L6

pop ebx
mov mainc, ebx

push offset printline
call outstr


push offset L7
call outstr


push mainc
push L3
push mainc
pop ebx
pop eax
imul eax, ebx
push eax
pop ebx
pop eax
sub eax, ebx
push eax
push L8
pop ebx
pop eax
sub eax, ebx
push eax

pop ebx
mov mainc, ebx


push mainc
call outnum



push mainc
call module
push eax

pop ebx
mov mainc, ebx

push offset printline
call outstr


push offset L9
call outstr



push mainc
call outnum


push offset printline
call outstr


push offset L10
call outstr



push mainc
call sqroot
push eax

pop ebx
mov mainc, ebx


push mainc
call outnum


push offset printline
call outstr


push offset L11
call outstr


push mainc
push L3
pop ebx 
pop eax
cdq
idiv ebx
push edx

pop ebx
mov mainc, ebx


push mainc
call outnum


push 0
call ExitProcess
main ENDP
end main
