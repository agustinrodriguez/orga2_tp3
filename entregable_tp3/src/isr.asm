; ** por compatibilidad se omiten tildes **
; ==============================================================================
; TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
; ==============================================================================
; definicion de rutinas de atencion de interrupciones

%include "imprimir.mac"

BITS 32

sched_tarea_offset:     dd 0x00
sched_tarea_selector:   dw 0x00
contador_reloj:      dd 0
contador_pause:      db 0

;; PIC
extern fin_intr_pic1

;; Sched
extern sched_proximo_indice
extern dame_actual
;; Game
extern game_mover
extern game_misil
extern game_minar
extern tss_idle
extern estado_error
extern desalojar_tarea
extern print_error
extern sched_proximo_indice
extern sched_proximo_idle
extern gama_inicializar
extern print_tablaerror
extern imprimir_desalojo
extern imprimir_reloj_tanque
extern matar_tarea_actual
extern imprimo_tss
extern sched
extern cambiar_estado
extern dame_estado
extern guardar_desalojo
;;
;; Definición de MACROS
;; -------------------------------------------------------------------------- ;;

%macro ISR 1
global _isr%1

_isr%1:
.loopear:
    ; To Infinity And Beyond!!
    cli
    xor ecx, ecx
    mov ecx, %1
 
    mov ecx, %1
    push ecx
    call guardar_desalojo
    pop ecx
    call dame_actual
    push eax
    call imprimo_tss
    add esp, 4
  ;  call print_tablaerror
    call matar_tarea_actual
    call vuelvo_idle
    sti
    jmp $
    iret
%endmacro

;;
;; Datos
;; -------------------------------------------------------------------------- ;;
; Scheduler
isrnumero:           dd 0x00000000
isrClock:            db '|/-\'
limpieza:            db '    '
offset:                 dd 0
selector:               dw 0
uno:                 db '1'
dos:                 db '2'
tres:                db '3'
cuatro:              db '4'
cinco:              db '5'
seis:              db '6'
siete:              db '7'
ocho:              db '8'
nueve:              db '9'
cero:              db '0'

;;
;; Rutina de atención de las EXCEPCIONES
;; -------------------------------------------------------------------------- ;;
ISR 0
ISR 1
ISR 2
ISR 3
ISR 4
ISR 5
ISR 6
ISR 7
ISR 8
ISR 9
ISR 10
ISR 11
ISR 12
ISR 13
ISR 14
ISR 15
ISR 16
ISR 17
ISR 18
ISR 19


global invalida
invalida:
   cli
    pushad
    CALL fin_intr_pic1
    CALL print_error ; en este tengo q devolver error y nada mas
    popad
    sti
    iret
;;
;; Rutina de atención del RELOJ
;; -------------------------------------------------------------------------- ;;

global _isr32
_isr32:
    cli  
    pushad   

    call proximo_reloj

    call screen_proximo_reloj   

    call dame_estado
    CMP eax, 1
    jne .prox_indice
    
    
    ;xchg bx,bx
    call dame_actual
    CMP ax, 0
    je .nojump
    call sched_proximo_idle
    jmp .sigo_jump_far

    .prox_indice:
        call sched_proximo_indice

    .sigo_jump_far:
        cmp ax, 0   
        je  .nojump  
              
        mov [selector], ax

        call fin_intr_pic1

        jmp far [offset]
        jmp .end
      
    .nojump:
        call fin_intr_pic1
        jmp .end 

    .end:
        popad
        sti
        iret


global screen_proximo_reloj
screen_proximo_reloj:
    ; cli
    pushad
    push ecx
    mov ecx, [contador_reloj]
    
    cmp ecx, 0
    je .primero
    cmp ecx, 1
    je .segundo
    cmp ecx, 2
    je .tercero
    cmp ecx, 4
    je .cuarto
    cmp ecx, 5
    je .quinto

    .primero:
        push ecx
        call imprimir_reloj_tanque
        pop ecx
        inc ecx
        mov [contador_reloj], ecx
        jmp .fin

    .segundo:
        push ecx
        call imprimir_reloj_tanque
        pop ecx
        inc ecx
        mov [contador_reloj], ecx

        jmp .fin

    .tercero:
        push ecx
        call imprimir_reloj_tanque
        pop ecx
        inc ecx
        mov [contador_reloj], ecx
        jmp .fin

    .cuarto:
        push ecx
        call imprimir_reloj_tanque
        pop ecx
        inc ecx
        mov [contador_reloj], ecx
        jmp .fin

    .quinto:
        push ecx
        call imprimir_reloj_tanque
        pop ecx
        xor ecx,ecx
        mov [contador_reloj], ecx
        jmp .fin

.fin:
    popad
    ;sti
    pop ecx
    ret

;;
;; Rutina de atención del TECLADO
;; -------------------------------------------------------------------------- ;;
global int_teclado
int_teclado:
    cli
    pushad
    xor al, al
    in al, 0x60
    mov ah, al
    or al, 0x80             
    out 0x61, al            ;Lo envio al controlador de teclado
    mov al, ah
    out 0x61, al            ;Vuelvo a como estaba antes el controlador.
    and ah, 0x80            ;me quedo con el valor sacandole el 80 
    jnz .fin_teclado
    mov ecx, cr0
    mov [estado_error+36], ecx
    mov ecx, cr2
    mov [estado_error+40], ecx
    mov ecx, cr3
    mov [estado_error+44], ecx
    MOV ebx, 0x00
    jmp .losQueSiSeUsan

.el1:
    ;mov eax, al
    dec eax
    push eax
    call imprimo_tss
    ;pop eax
    add esp,4
    jmp .fin_teclado

.el2:
    dec eax
    push eax
    call imprimo_tss
    ;pop eax
    add esp,4
    jmp .fin_teclado

.el3:
    dec eax
    push eax
    call imprimo_tss
    ;pop eax
    add esp,4
    jmp .fin_teclado

.el4:
    dec eax
    push eax
    call imprimo_tss
    ;pop eax
    add esp,4
    jmp .fin_teclado

.el5:
    dec eax
    push eax
    call imprimo_tss
    ;pop eax
    add esp,4
    jmp .fin_teclado

.el6:
    dec eax
    push eax
    call imprimo_tss
    ;pop eax
    add esp,4
    jmp .fin_teclado

.el7:
    dec eax
    push eax
    call imprimo_tss
    ;pop eax
    add esp,4
    jmp .fin_teclado

.el8:
    dec eax
    push eax
    call imprimo_tss
    ;pop eax
    add esp,4
    jmp .fin_teclado

.elp:
.aPause:
    call dame_estado
    CMP eax, 0
    ;xchg bx,bx
    jne .continuo
    mov eax, 1
    mov [contador_pause],eax
    push eax
    call cambiar_estado
    ;pop eax
    add esp,4
    jmp .fin_teclado

.continuo:
    MOV EAX, 0
    push eax
    call cambiar_estado
    ;pop eax
    add esp,4
    jmp .fin_teclado

.losQueSiSeUsan:
    cmp al, 0x02
    je .el1
    
    cmp al, 0x03
    je .el2
    
    cmp al, 0x04
    je .el3
    
    cmp al, 0x05
    je .el4
    
    cmp al, 0x06
    je .el5
    
    cmp al, 0x07
    je .el6
    
    cmp al, 0x08
    je .el7
    
    cmp al, 0x09
    je .el8
    
    cmp al, 0x19
    je .elp
    
   ; cmp al, 0x2e
   ; je .elc

.losQueNoSeUsan:
    CMP EAX, ebx
    je .fin_teclado
    ADD ebx, 0x01
    jmp .losQueNoSeUsan


.fin_teclado:
    call fin_intr_pic1
    popad
    iret

;; TASK
;; ---------------------------------------------------------------
global int_task
int_task:
    cli
    push eax
    call dame_actual
    mov edi, eax
    pop eax
    CMP EAX, 0x83D
    je .moviendo
    CMP EAX, 0x911
    je .misil
    CMP EAX, 0x355
    je .minar
    .moviendo: 
    ;tiene un solo parametro q va por ebx
        push ebx 
        push edi
        call game_mover
        add esp, 8
        jmp .fin
    .misil:
        push esi
        push edx
        push ecx
        push ebx
        push edi
        call game_misil
        add esp, 20
        jmp .fin

    .minar: 
        push ebx
        push edi
        call game_minar
        add esp,8
        jmp .fin

    .fin:
    push eax
    call fin_intr_pic1
    call vuelvo_idle
    pop eax
    sti
    ;popad
    iret
;;

global vuelvo_idle
vuelvo_idle:
    pushad
    call sched_proximo_idle   
    mov [selector], ax
    sti
    jmp far [offset]
    popad
    sti
    ret

;; Rutinas de atención de las SYSCALLS
;; -------------------------------------------------------------------------- ;;
%define SYS_MOVER     0x83D
%define SYS_MISIL     0x911
%define SYS_MINAR     0x355

;; Funciones Auxiliares
;; -------------------------------------------------------------------------- ;;
global proximo_reloj
proximo_reloj:
        pushad
        inc DWORD [isrnumero]
        mov ebx, [isrnumero]
        cmp ebx, 0x4
        jl .ok
                mov DWORD [isrnumero], 0x0
                mov ebx, 0
        .ok:
                add ebx, isrClock
                imprimir_texto_mp ebx, 1, 0x0f, 49, 79
                popad
        ret
        
        
