section .data
   msg:  DB 'Me Quiero ir en'
   largo EQU $ - msg
   nume: DB '9'
   len0 EQU $ - nume
   enter: DB 10
   lenter EQU $ - enter
   fin:  DB 'Chau!', 10
   len1 EQU $ - fin
global _start
section .text
   _start:
   mov esi, 9    ; set 9
   _ciclo:
   mov rax, 4     ; funcion 4
   mov rbx, 1     ; stdout
   mov rcx, msg   ; mensaje
   mov rdx, largo ; longitud
   int 0x80
   mov rcx, nume  ; mensaje
   mov rdx, len0     ; longitud
   int 0x80
   mov rcx, enter  ; mensaje
   mov rdx, lenter     ; longitud
   int 0x80
   dec byte [nume]
   dec esi
   cmp esi, 0
   jnz _ciclo
   mov rcx, fin  ; mensaje
   mov rdx, len1     ; longitud
   int 0x80
   mov rax, 1
   mov rbx, 0
   int 0x80
