section .data
	n: db 2
	msg1: db "System is Little Endian"
	str1: equ $ - msg1
	msg2: db "System is Big Endian"
	str2: equ $ - msg2

section .text
	global _start

_start:
	;big 	--> 0 1 2
	;little --> 2 1 0

	mov al, byte [n]
	; n --> 0x100 
	cmp al,0
	je _little
	jne _big

	mov eax,1
	xor ebx,ebx
	int 0x80

_little:
	mov eax,4
	mov ebx,1
	mov ecx,msg1
	mov edx,str1
	int 0x80

	mov eax,1
	mov ebx,0
	int 0x80

_big:
	mov eax,4
	mov ebx,1
	mov ecx,msg2
	mov edx,str2
	int 0x80

	mov eax,1
	mov ebx,0
	int 0x80
