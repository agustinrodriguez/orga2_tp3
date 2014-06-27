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
;;
;; Definición de MACROS
;; -------------------------------------------------------------------------- ;;

%macro ISR 1
global _isr%1

_isr%1:
.loopear:
    ; To Infinity And Beyond!!
    cli
   ; xchg bx,bx
    xor ecx, ecx
    mov ecx, %1
    ;hago los q tengo en pila
    mov [estado_error], eax ; EAX
    mov eax, ds
    mov [estado_error+52], eax ;ds
     ;mov eax, eip
    pop eax ; error code

    pop eax
    mov [estado_error+32], eax ;eip
    ;mov eax, cs
    pop eax 
    mov [estado_error+48], eax ;cs
   ; mov eax, ds 

    pop eax
    mov [estado_error+72], eax ;eflags

    push eax ; alineo pila

    mov eax, ebx
    mov [estado_error+4], eax
    mov eax, ecx
    mov [estado_error+8], eax
    mov eax, edx    
    mov [estado_error+12], eax
    mov eax, esi
    mov [estado_error+16], eax
    mov eax, edi
    mov [estado_error+20], eax
    mov eax, ebp
    mov [estado_error+24], eax
    mov eax, esp
    mov [estado_error+28], eax
    mov eax, cr0
    mov [estado_error+36], eax
    mov eax, cr2
    mov [estado_error+40], eax
    mov eax, cr3
    mov [estado_error+44], eax
    mov eax, es
    mov [estado_error+56], eax
    mov eax, fs
    mov [estado_error+60], eax
    mov eax, gs
    mov [estado_error+64], eax
    mov eax, ss    ;mov eax, ss
    mov [estado_error+68], eax

    push ecx
    call imprimir_desalojo
    pop ecx
    call print_tablaerror
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
      
      call sched_proximo_indice   
      
      cmp ax, 0   
      je  .nojump  
              
      mov [selector], ax
      
      call fin_intr_pic1

      popad
      sti
     ; xchg bx,bx
      jmp far [offset]
      cli
      pushad
      jmp .end   
      
    .nojump:   
  
        call fin_intr_pic1   
    
    .end: 

        popad
        sti
        iret


global screen_proximo_reloj
screen_proximo_reloj:
    ; cli
    pushad
   ; call fin_intr_pic1
   push ecx
    mov ecx, [contador_reloj]
   ; xchg bx, bx  ;Break para ver como va moviendose el cursor 
    
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
        ;imprimir_texto_mp isrClock, 2, 0x0f, 47, 59
        push ecx
        call imprimir_reloj_tanque
        pop ecx
        inc ecx
        mov [contador_reloj], ecx

        jmp .fin

    .tercero:
        ;imprimir_texto_mp isrClock, 3, 0x0f, 47, 59
        push ecx
        call imprimir_reloj_tanque
        pop ecx
        inc ecx
        mov [contador_reloj], ecx
        jmp .fin

    .cuarto:
        ;imprimir_texto_mp isrClock, 4, 0x0f, 47, 59
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
        ;imprimir_texto_mp limpieza, 4, 0x0f, 47, 59
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
    push eax
    call dame_actual
    mov edi, eax
    pop eax
    xchg bx, bx
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
        push ebx
        push ecx
        push edx
        push esi
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
    call fin_intr_pic1
    call vuelvo_idle
    sti
    popad
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
        
        
