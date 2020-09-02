%define NULL 0
; Completar!

; En mac, las funciones llevan un _ adelante
; En caso de mac, _printf

; En caso de mac, global _mostrarAlumno
global dist
global normalizarVector

section .data


section .text

; En caso de mac, _mostrarAlumno
; Me llega por RDI el PUNTERO a la estructura
dist:
	push rbp
	mov rbp, rsp
	;pila alineada
	pxor xmm2, xmm2
	xor rcx, rcx 
	mov cx, dx 
	shr cx, 1
	_clc:	movups xmm0, [rdi]
			movups xmm1, [rsi]
			;te los registroos
			subps xmm0, xmm1
			;los resto
			mulps xmm0, xmm0
			;cuadrado
			movups xmm1, xmm0
			psrldq xmm1, 4
			addps xmm0, xmm1
			;sumo
			sqrtps xmm1, xmm0
			;raiz cuadrada
			maxps xmm2, xmm1
			add rdi, 16
			add rsi, 16
			loop _clc
	movups xmm1, xmm2
	psrldq xmm1, 8
	maxps xmm1, xmm2
	; Desencolo
	pop rbp
	ret

normalizarVector:	
	push rbp
	mov rbp, rsp
	push rbx
	sub rsp, 8
	;pila alineada
	mov rbx, rdi
	pxor xmm2, xmm2
	pxor xmm3, xmm3
	xor rcx, rcx 
	mov ecx, esi
	shr ecx, 2
	_dMinMax:	movups xmm1, [rbx]
				;tengo los registroos
				maxps xmm2, xmm1
				minps xmm3, xmm1
				;tengo los minimos y los maximos 
				add rbx, 16
				;loop _dMinMax
			movups xmm1, xmm2
			psrldq xmm1, 8
			maxps xmm2, xmm1
			movups xmm1, xmm2
			psrldq xmm1, 4
			maxps xmm2, xmm1
			;max en xmm2 pos 0 	
			movups xmm1, xmm3
			psrldq xmm1, 8
			minps xmm3, xmm1
			movups xmm1, xmm3
			psrldq xmm1, 4
			minps xmm3, xmm1
			;min en xmm3 pos 0
	;restablesco valores
	mov ecx, esi
	shr ecx, 2
	mov rbx, rdi
	;genero vector max
	pxor xmm4, xmm4
	movups xmm4, xmm2
	pslldq xmm4, 4
	maxps xmm2, xmm4
	movups xmm4, xmm2
	pslldq xmm4, 8
	maxps xmm2, xmm4
	;genero vector min
	pxor xmm4, xmm4
	movups xmm4, xmm3
	pslldq xmm4, 4
	minps xmm3, xmm4
	movups xmm4, xmm3
	pslldq xmm4, 8
	minps xmm3, xmm4
	; genero max-min
	subps xmm2, xmm3
	_normalizo:	movups xmm1, [rbx]
				;tengo los registroos
				subps xmm1, xmm3
				divps xmm1, xmm2
				movdqu [rbx], xmm1 
				;normalizado
				add rbx, 16
				loop _normalizo
	;devuelvo puntero
	mov rax, rdi			
	; Desencolo
	add rsp, 8
	pop rbx
	pop rbp
	ret