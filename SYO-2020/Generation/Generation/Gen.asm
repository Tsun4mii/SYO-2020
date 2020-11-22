.586
.model flat, stdcall
includelib libucrt.lib
includelib kernel32.lib
includelib "../Debug/GenLib.lib
ExitProcess PROTO:DWORD 
.stack 4096


 outnum PROTO : DWORD

 outstr PROTO : DWORD

 sqroot PROTO : DWORD

.const
		newline byte 13, 10, 0
		L1 sdword 3
		L2 sdword 5
		L3 sdword 20
		L4 sdword 2
		L5 sdword 154
		L6 sdword 100
		L7 sdword -75
		L8 byte 'hello world', 0
		L9 sdword 150
		L10 byte ' ', 0
		L11 sdword 10
		L12 byte '123456798', 0
.data
		temp sdword ?
		buffer byte 256 dup(0)
		fcs sdword 0
		mainz sdword 0
		mainx sdword 0
		mainy sdword 0
		mainf sdword 0
		maina dword ?
		mainsb dword ?
		mainsc dword ?
.code

;----------- fb ------------
fb PROC,
	fbt : sdword, fbn : sdword  
; --- save registers ---
push ebx
push edx
; ----------------------
push L1
push fbn
push L2
pop ebx
pop eax
add eax, ebx
push eax
pop ebx
pop eax
imul eax, ebx
push eax

pop ebx
mov fbt, ebx

mov edx, fbt
cmp edx, L3

jl cycle1
jmp cyclenext1
cycle1:
push fbt
push L4
pop ebx
pop eax
add eax, ebx
push eax

pop ebx
mov fbt, ebx

mov edx, fbt
cmp edx, L3

jl cycle1
cyclenext1:
; --- restore registers ---
pop edx
pop ebx
; -------------------------
mov eax, fbt
ret
fb ENDP
;------------------------------


;----------- fc ------------
fc PROC,
	fcp : sdword  
; --- save registers ---
push ebx
push edx
; ----------------------
push L5

pop ebx
mov fcs, ebx

push fcp
push fcs
pop ebx
pop eax
add eax, ebx
push eax

pop ebx
mov fcp, ebx


push fcp
call sqroot
push eax

pop ebx
mov fcp, ebx

; --- restore registers ---
pop edx
pop ebx
; -------------------------
mov eax, fcp
ret
fc ENDP
;------------------------------


;----------- MAIN ------------
main PROC
push L6

pop ebx
mov mainx, ebx

push L1

pop ebx
mov mainy, ebx

push L7

pop ebx
mov mainf, ebx

mov maina, offset L8
mov edx, mainy
cmp edx, L9

jl cycle2
jmp cyclenext2
cycle2:

push offset L10
call outstr



push mainy
call outnum


push mainy
push L11
pop ebx
pop eax
add eax, ebx
push eax

pop ebx
mov mainy, ebx

mov edx, mainy
cmp edx, L9

jl cycle2
cyclenext2:

push mainx
call sqroot
push eax

pop ebx
mov mainz, ebx


push mainy
push mainx
call fb
push eax

pop ebx
mov mainz, ebx


push maina
call outstr


mov mainsb, offset L12
mov mainsc, offset L12

push mainy
call outnum



push offset L10
call outstr



push mainz
call outnum



push mainf
call outnum


push 0
call ExitProcess
main ENDP
end main
