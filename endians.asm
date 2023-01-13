; NASM Assembly kullanılarak sistemin Big-Endian mı yoksa Little-Endian mı olduğunu gösteren Assembly Programı.

section .data
	n: db 1
	msg1: db "System is Little Endian"
	str1: equ $ - msg1
	msg2: db "System is Big Endian"
	str2: equ $ - msg2

; Dikkat edilmesi gereken şey ise, Little-Endian'da 1 bytelık değerin yazılması 1 ile başlanmasıdır. Dolasıyla bu programda 1 byte değer üzerinden kontrol 
; yapılarak sistemin Big mi yoksa Little mi olduğun anlaşılacaktır. 

section .text
	global _start

_start:
	mov al, byte [n] ; burada n değişken adresin içerisindeki değerin ilk byte'tını alır ve al register'a koyar.
	cmp al,1 ; burada ise alınan ilk byte'ın 1 olup olunmadığı kontrol edilir.
	je _little ; eğer alınan ilk byte 1 ise _little label'a git.
	jne _big   ; değil ise _big label'a git.

	;programdan çık.
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
