; ** por compatibilidad se omiten tildes **
; ==============================================================================
; TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
; ==============================================================================
; definicion de rutinas de atencion de interrupciones

%include "imprimir.mac"

BITS 32

sched_tarea_offset:     dd 0x00
sched_tarea_selector:   dw 0x00
contador_reloj:      db 0

;; PIC
extern fin_intr_pic1

;; Sched
extern sched_proximo_indice
;; Game
extern game_mover
extern game_misil
extern game_minar

extern print_error
;;
;; Definición de MACROS
;; -------------------------------------------------------------------------- ;;

%macro ISR 1
global _isr%1

_isr%1:
.loopear:
    ; To Infinity And Beyond!!
    ;cli
    xor ecx, ecx
    mov ecx, %1
    push ecx
    call print_error
    pop ecx
    jmp $
    ;sti
    iret
%endmacro

;;
;; Datos
;; -------------------------------------------------------------------------- ;;
; Scheduler
isrnumero:           dd 0x00000000
isrClock:            db '|/-\'
limpieza:            db '    '
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
global screen_proximo_reloj
screen_proximo_reloj:
    cli
    pushad
    call fin_intr_pic1
    mov eax, [contador_reloj]
  ;  xchg bx, bx  Break para ver como va moviendose el cursor 
    
    cmp eax, 0
    je .primero
    cmp eax, 1
    je .segundo
    cmp eax, 2
    je .tercero
    cmp eax, 4
    je .cuarto
    cmp eax, 5
    je .quinto

    .primero:
        imprimir_texto_mp isrClock, 1, 0x0f, 47, 59
        inc eax
        mov [contador_reloj], eax
        jmp .fin

    .segundo:
        imprimir_texto_mp isrClock, 2, 0x0f, 47, 59
        inc eax
        mov [contador_reloj], eax
        jmp .fin

    .tercero:
        imprimir_texto_mp isrClock, 3, 0x0f, 47, 59
        inc eax
        mov [contador_reloj], eax
        jmp .fin

    .cuarto:
        imprimir_texto_mp isrClock, 4, 0x0f, 47, 59
        inc eax
        mov [contador_reloj], eax
        jmp .fin

    .quinto:
        imprimir_texto_mp limpieza, 4, 0x0f, 47, 59
        xor eax,eax
        mov [contador_reloj], eax
        jmp .fin

.fin:
    popad
    sti
    iret

;;
;; Rutina de atención del TECLADO
;; -------------------------------------------------------------------------- ;;
global int_teclado
int_teclado:
    cli
    pushad
    xor al, al
    xchg bx, bx
    in al, 0x60
    mov ah, al
    or al, 0x80             
    out 0x61, al            ;Lo envio al controlador de teclado
    mov al, ah
    out 0x61, al            ;Vuelvo a como estaba antes el controlador.
    and ah, 0x80            ;me quedo con el valor sacandole el 80 
    jnz .fin_teclado
    
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
    
    cmp al, 0x0a
    je .el9
    
    cmp al, 0x0b
    je .el0

.el1:
    imprimir_texto_mp uno, 1, 0x0f, 10, 10
    jmp .fin_teclado

.el2:
    imprimir_texto_mp dos, 1, 0x0f, 10, 10
    jmp .fin_teclado

.el3:
    imprimir_texto_mp tres, 1, 0x0f, 10, 10
    jmp .fin_teclado

.el4:
    imprimir_texto_mp cuatro, 1, 0x0f, 10, 10
    jmp .fin_teclado

.el5:
    imprimir_texto_mp cinco, 1, 0x0f, 10, 10
    jmp .fin_teclado

.el6:
    imprimir_texto_mp seis, 1, 0x0f, 10, 10
    jmp .fin_teclado

.el7:
    imprimir_texto_mp siete, 1, 0x0f, 10, 10
    jmp .fin_teclado

.el8:
    imprimir_texto_mp ocho, 1, 0x0f, 10, 10
    jmp .fin_teclado

.el9:
    imprimir_texto_mp nueve, 1, 0x0f, 10, 10
    jmp .fin_teclado

.el0:
    imprimir_texto_mp cero, 1, 0x0f, 10, 10
    jmp .fin_teclado

.fin_teclado:
    call fin_intr_pic1
    popad
    sti
    iret

;; TASK
;; ---------------------------------------------------------------
global int_task
int_task:
    pushad ;esto puede no ser necesario chequear!
    cli
    CMP EAX, 0x83D
    je .moviendo
    CMP EAX, 0x911
    je .misil
    CMP EAX, 0x355
    je .minar
    .moviendo:

        jmp .fin
    .misil:
        jmp .fin

    .minar: 
        jmp .fin

    .fin:
    sti
    popad
    iret
;;
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
        
        
