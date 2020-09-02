  ; FUNCIONES de C
  extern malloc
  extern free
  extern fprintf
   
; FUNCIONES
  global ct_new
  global ct_delete
  global ct_print
  global ctIter_new
  global ctIter_delete
  global ctIter_first
  global ctIter_next
  global ctIter_get
  global ctIter_valid

; OFFSETS:
  %define NODESIZE 3          ;offset para tam. elementos
  %define NULL 0              ;NULL == 0
  %define TRUE 1
  %define FALSE 0

  ;************NODO************

  %define off_N_father 0     ;offset al puntero al padre
  %define off_N_elements 8    ;offset a los elementos 
  %define off_N_fstElm 8      ;offset al primer elemento
  %define off_N_sndElm 12     ;offset al segundo elemento
  %define off_N_trdElm 16     ;offset al tercer elemento
  %define off_N_nxtElm 4      ;offset para prox. elemento
  %define off_N_len 20        ;offset a elementos validos
  %define off_N_child 21      ;offset a los hijos
  %define off_N_fstChild 21   ;offset al primer hijo
  %define off_N_sndChild 29   ;offset al segundo hijo
  %define off_N_trdChild 37   ;offset al tercer hijo
  %define off_N_forChild 45   ;offset al cuarto hijo
  %define off_N_nxtChild 8    ;offset para prox. hijo

  %define size_node 53

  ;************ITERADOR************

  %define off_I_tree 0        ;offset al puntero a arbol
  %define off_I_node 8        ;offset al puntero a nodo actual
  %define off_I_pos 16        ;offset al indicador de posicion en elementos
  %define off_I_count 17      ;offset al contador

  %define size_iter 21

  ;************TREE************

  %define off_T_root 0        ;offset a la raiz
  %define off_T_size 8        ;offset al tamaño del arbol

  %define size_tree 12  

section .data
  etiq: db "%d", 10

section .text

; =====================================
; void ct_new(ctTree** pct);  ;RDI <- pct
ct_new: 
        push rbp
        mov rbp, rsp
        push rbx
        sub rsp, 8
        ; pila alineada
        mov rbx, rdi                     ;pongo **ctTree en rbx
        mov rdi, size_tree
        call malloc                        ;tengo en rax el *tree
        mov qword [rax+off_T_root], NULL   ;seteo a null el puntero al nodo
        mov dword [rax+off_T_size], 0      ;tamaño en cero
        mov [rbx], rax
        add rsp, 8                         ;desarmo pila
        pop rbx
        pop rbp
        ret

; =====================================
; void ct_delete(ctTree** pct);
ct_delete:
          push rbp
          mov rbp, rsp
          push rbx
          sub rsp, 8
          ; pila alineada
          mov rbx, [rdi]                    ;pongo *ctTree en rbx
          cmp qword [rbx+off_T_root], NULL  ;me fijo si esta vacio
          jz .fin 
          mov rdi, [rbx+off_T_root]
          call node_Del
    .fin: mov rdi, rbx                      ;pongo *ctTree en rdi
          call free                         ;libero memoria
          add rsp, 8                        ;desarmo pila
          pop rbx
          pop rbp
          ret

; =====================================
; void node_Del(ctNode* n_ptr);
node_Del:
          push rbp
          mov rbp, rsp
          push rbx
          push r12
          push r13
          push r14
          push r15
          sub rsp, 8
          ; pila alineada
          mov rbx, rdi                      ;pongo n_ptr en rbx
          cmp rbx, NULL                     ;si es NULL no tengo nada que liberar
          jz .fin
          mov r12, [rbx+off_N_fstChild]     ;guardo los punteros a
          mov r13, [rbx+off_N_sndChild]     ;los hijos
          mov r14, [rbx+off_N_trdChild]
          mov r15, [rbx+off_N_forChild]
          mov rdi, rbx
          call free                         ;libero el nodo actual
          mov rdi, r12                      ;recursion sobre los hijos
          call node_Del
          mov rdi, r13
          call node_Del
          mov rdi, r14
          call node_Del
          mov rdi, r15
          call node_Del               
    .fin: add rsp, 8                        ;desarmo pila
          pop r15
          pop r14
          pop r13
          pop r12
          pop rbx
          pop rbp
          ret

; ; =====================================
; ; void ct_aux_print(FILE *pfile, ctNode* node);
ct_aux_print:
          push rbp
          mov rbp, rsp
          push rbx
          push r12
          ; pila alineada
          mov rbx, rsi
          cmp rbx, NULL
          jz .fin
          mov r12, rdi
          ;imprimo primer hijo
          mov rsi, [rbx+off_N_fstChild]
          call ct_aux_print
          ;imprimo el primer elemento
          mov rdi, r12
          mov rsi, etiq     
          mov edx, [rbx+off_N_fstElm]
          call fprintf
          ;imprimo segundo hijo
          mov rdi, r12
          mov rsi, [rbx+off_N_sndChild]
          call ct_aux_print
          ;imprimo el segundo elemento
          cmp dword [rbx+off_N_sndElm], 0
          jz .fin
          mov rdi, r12
          mov rsi, etiq     
          mov edx, [rbx+off_N_sndElm]
          call fprintf
          ;imprimo tercer hijo
          mov rdi, r12
          mov rsi, [rbx+off_N_trdChild]
          call ct_aux_print
          ;imprimo el tercer elemento
          cmp dword [rbx+off_N_trdElm], 0
          jz .fin
          mov rdi, r12
          mov rsi, etiq     
          mov edx, [rbx+off_N_trdElm]
          call fprintf
          ;imprimo cuarto hijo
          mov rdi, r12
          mov rsi, [rbx+off_N_forChild]
          call ct_aux_print
  .fin:   pop r12                       ;desarmo pila
          pop rbx
          pop rbp
          ret

; ; =====================================
; ; void ct_print(ctTree* ct, FILE *pfile);
ct_print:
        push rbp
        mov rbp, rsp
        push rbx
        sub rsp, 8
        ; pila alineada
        mov rbx, rsi                      ;guardo puntero a file
        mov rsi, [rdi+off_T_root]         ;seteo en rsi el puntero a la raiz
        mov rdi, rbx                      ;seteo en rdi el puntero a FILE
        call ct_aux_print
        add rsp, 8                        ;desarmo pila
        pop rbx
        pop rbp
        ret


; =====================================
; ctIter* ctIter_new(ctTree* ct);
ctIter_new:
        push rbp
        mov rbp, rsp
        push rbx
        sub rsp, 8
        ; pila alineada
        mov rbx, rdi                      ;pongo ct en rbx
        mov rdi, size_iter                
        call malloc                       ;reservo memoria para el iterador, ademas
                                          ;me deja en RAX el puntero al iterador para el return
        mov [rax+off_I_tree], rbx         ;seteo el puntero al tree
        mov qword [rax+off_I_node], NULL  ;nodo actual en NULL
        mov byte [rax+off_I_pos], 0       ;current en 0
        mov dword [rax+off_I_count], 0    ;contador en 0
        add rsp, 8                        ;desarmo pila
        pop rbx
        pop rbp
        ret

; =====================================
; void ctIter_delete(ctIter* ctIt);
ctIter_delete:
        push rbp
        mov rbp, rsp
        ; pila alineada
        call free         ;libero el iterador
        pop rbp           ;desarmo pila
        ret
; =====================================
; void ctIter_first(ctIter* ctIt);
ctIter_first:
            push rbp
            mov rbp, rsp
            push rbx
            push r12
            ;pila alineada
            mov rbx, [rdi+off_I_tree]         ;pongo en rbx el puntero al tree
            mov r12, [rbx+off_T_root]         ;pongo en r12 el puntero al nodo
            cmp r12, NULL                     ;si el raiz es null, esta vacio
            jz .asig 
  .noNil:   cmp qword [r12+off_N_fstChild], NULL    ;me fijo si tiene hijo izquierdo
            jz .asig
            mov r12, [r12+off_N_fstChild]     ;seteo en r12 el puntero al hijo izq   
            jmp .noNil
  .asig:    mov [rdi+off_I_node], r12         ;pongo el puntero al minimo en nodo apuntado
            ; si entro porque r12 == NULL, entonces setea NULL
            mov byte [rdi+off_I_pos], 0       ;current en 0
            mov dword [rdi+off_I_count], 1    ;count en 1
            pop r12                           ;desarmo pila
            pop rbx
            pop rbp
            ret

; =====================================
; void ctIter_next(ctIter* ctIt);
ctIter_next:
          
          push rbp
          mov rbp, rsp
          push rbx
          push r12
          push r13
          push r14
          ;pila alineada
          xor rbx, rbx
          xor r13, r13
          mov r14, rdi
          mov bl, [rdi+off_I_pos]
          inc bl                      ;posicion mas uno
          mov r12, [rdi+off_I_node]
          cmp qword [r12+rbx*off_N_nxtChild+off_N_child], NULL  ;guarda 1
          jnz .hijos
          mov r13b, [r12+off_N_len]   
          dec r13b                    ;tamaño nodo menos uno
          cmp bl, r13b                ;guarda 2 (pregunta si bl > r13b)
          jg .up
          mov [r14+off_I_pos], bl           ;seteo la posicion
          add dword [r14+off_I_count], 1    ;incremento el contador
          jmp .fin
  .up:    call ctIter_aux_up           
          jmp .fin
  .hijos: mov r13, [r12+rbx*off_N_nxtChild+off_N_child]
          mov [r14+off_I_node], r13
          mov rdi, r14 
          call ctIter_aux_down
  .fin:   pop r14                           ;desarmo pila
          pop r13
          pop r12
          pop rbx
          pop rbp
          ret

; =====================================
;void ctIter_aux_up(ctIter* ctIt)
ctIter_aux_up:
            push rbp
            mov rbp, rsp
            push rbx
            push r12
            ;pila alineada
            mov rbx, rdi
            mov r12, [rbx+off_I_node]
  .guarda:  cmp qword [r12+off_N_father], NULL
            jz .inval
            mov rdi, r12
            mov rsi, [r12+off_N_father]
            call ctIter_aux_isIn             ;tengo en RAX la posicion del puntero padre-hijo
            mov r12, [r12+off_N_father]
            cmp eax, 3
            jl .nextOk
            jmp .guarda
  .nextOk:  mov [rbx+off_I_node], r12         ;seteo el nodo apuntado         
            mov [rbx+off_I_pos], al           ;seteo la posicion(i), deberia estar en AL, ya que i e [0..3]
            add dword [rbx+off_I_count], 1    ;incremento el contador
            jmp .fin
  .inval:   mov qword [rbx+off_I_node], NULL   ;INVALIDO el iterador        
  .fin:     pop r12                            ;desarmo pila
            pop rbx
            pop rbp             
            ret        
; =====================================
;uint32_t ctIter_aux_isIn(ctNode* current, ctNode* father)
ctIter_aux_isIn:            
            push rbp
            mov rbp, rsp
            ;pila alineada
            xor rax, rax    ;RESET a RAX, deberia funcionar esperando el resultado en eax o al,
                            ; ya que en C2 tienen la misma representacion en 1,4 y 8 bytes.
  .check:   cmp rdi, [rsi+rax*off_N_nxtChild+off_N_child]
            jz .find
            inc rax
            jmp .check
  .find:    pop rbp                 ;desarmo pila
            ret


; =====================================
; void ctIter_aux_down(ctIter* ctIt)
ctIter_aux_down:  
            push rbp
            mov rbp, rsp
            push rbx
            sub rsp, 8
            ;pila alineada
            mov rbx, [rdi+off_I_node]
  .noNil:   cmp qword [rbx+off_N_fstChild], NULL    ;me fijo si tiene hijo izquierdo
            jz .asig
            mov rbx, [rbx+off_N_fstChild]     ;seteo en rbx el puntero al hijo izq   
            jmp .noNil
  .asig:    mov [rdi+off_I_node], rbx         ;pongo el puntero al minimo en nodo apuntado
            mov byte [rdi+off_I_pos], 0       ;current en 0, FALTA EL CONTADOR
            add dword [rdi+off_I_count], 1    ;incremento el contador
            add rsp, 8                        ;desarmo pila
            pop rbx
            pop rbp
            ret



; =====================================
; uint32_t ctIter_get(ctIter* ctIt);
ctIter_get:
            push rbp
            mov rbp, rsp
            push rbx
            push r12
            ;pila alineada
            cmp qword [rdi+off_I_node], NULL   ;me fijo si el puntero es valido
            jnz .valid
            mov eax, 0                         ;el nodo apuntado es NULL, devuelvo CERO
            jmp .fin
  .valid:   mov rbx, [rdi+off_I_node]          ;pongo en rbx el puntero al nodo
            xor r12, r12                       ;r12 <- 0
            mov r12b, [rdi+off_I_pos]              ;pongo en r12b la posicion del arreglo de elementos
            mov eax, [rbx+r12*off_N_nxtElm+off_N_elements]   ;pongo en eax el nodo apuntado 
  .fin      pop r12                            ;desarmo pila
            pop rbx
            pop rbp             
            ret

; =====================================
; uint32_t ctIter_valid(ctIter* ctIt);
ctIter_valid:
            push rbp
            mov rbp, rsp
            ;pila alineada
            cmp qword [rdi+off_I_node], NULL   ;me fijo si el puntero es valido
            jnz .valid
            mov eax, FALSE                     ;seteo False
            jmp .fin
  .valid:   mov eax, TRUE                      ;seteo true
  .fin:     pop rbp                            ;desarmo pila
            ret