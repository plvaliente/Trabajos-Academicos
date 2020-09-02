%define NULL 0
; Completar!
%define offset_comision 0
; Completar!
%define offset_nombre 8
; Completar!
%define offset_edad 16

; En mac, las funciones llevan un _ adelante
; En caso de mac, _printf
extern printf

; En caso de mac, global _mostrarAlumno
global mostrarAlumno

section .data
	texto: db "Nombre: %s, comision: %hd, edad: %d", 0x0a, 0x00

section .text

; En caso de mac, _mostrarAlumno
; Me llega por RDI el PUNTERO a la estructura
mostrarAlumno:
	push rbp
	mov rbp, rsp
	; Pila alineada
	; Recordar pushear RBX, R12, R13, R14 y R15 si se utilizan
	;xor rdx, rdx
	mov rax, 1
	mov r8, rdi
	mov rdi, texto
	mov rsi, [r8+offset_nombre]
	mov dx, [r8+offset_comision]
	mov ecx, [r8+offset_edad]
	call printf
	; Desencolo
	pop rbp
	ret
