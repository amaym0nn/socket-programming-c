; Assembly program that shows whether the system is Big-Endian or Little-Endian using NASM assembly

section .data
	n: db 1
	msg1: db "System is Little Endian"
	str1: equ $ - msg1
	msg2: db "System is Big Endian"
	str2: equ $ - msg2

;The thing to know is that writing a 1-byte value in Little-Endian starts with 1. Therefore, in this program, by controlling 
; 1 byte value, it will be understood whether the system is Big or Little.

section .text
	global _start

_start:
	mov al, byte [n] ; Where n takes the first byte of the value in the variable address and puts it in the al register.
	cmp al,1 ; Here, it is checked whether the first byte received is 1 or not.
	je _little ; If the first byte received is 1, go to the _little label. 
	jne _big   ; if not, go to _big label.

	; exit program 
	mov eax,1
	xor ebx,ebx
	int 0x80

_little:
	; print msg1 
	mov eax,4
	mov ebx,1
	mov ecx,msg1
	mov edx,str1
	int 0x80

	mov eax,1
	mov ebx,0
	int 0x80

_big:
	; print msg2
	mov eax,4
	mov ebx,1
	mov ecx,msg2
	mov edx,str2
	int 0x80

	mov eax,1
	mov ebx,0
	int 0x80