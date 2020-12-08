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

.const
		printline byte 13, 10, 0
		L1 sdword 3
		L2 sdword 5
		L3 sdword 20
.data
		temp sdword ?
		buffer byte 256 dup(0)
		mainx sdword 0
.code

;----------- MAIN ------------
main PROC
push L3
push L1

pop ebx
pop eax
cdq
idiv ebx
push edx 
mov eax, edx

pop eax 
mov mainx, eax

push mainx
call outnum


push 0
call ExitProcess
main ENDP
end main
