; ** por compatibilidad se omiten tildes **
; ==============================================================================
; TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
; ==============================================================================

%include "imprimir.mac"
%define MAINPAGEDIR             0x00027000
global start

; GDT
extern GDT_DESC
extern IDT_DESC

extern limpiar_pantalla
extern idt_inicializar
extern pantalla_juego
extern imprimir_nombre_grupo
extern mmu_inicializar
extern get_cr3_task
extern caracter_pintado
extern deshabilitar_pic
extern resetear_pic
extern habilitar_pic
extern tss_inicializar
extern gdt_set_tss
extern sched_inicializar
extern game_inicializar

;; Saltear seccion de datos
jmp start

;;
;; Seccion de datos.
;; -------------------------------------------------------------------------- ;;
iniciando_mr_msg db     'Iniciando kernel (Modo Real)...'
iniciando_mr_len equ    $ - iniciando_mr_msg

iniciando_mp_msg db     'Iniciando kernel (Modo Protegido)...'
iniciando_mp_len equ    $ - iniciando_mp_msg

equipo_mp_msg db     'Colombia/Arepa'
equipo_mp_len equ    $ - equipo_mp_msg

isrClock:            db '|/-\'

;;
;; Seccion de código.
;; -------------------------------------------------------------------------- ;;

;; Punto de entrada del kernel.
BITS 16
start:
    ; Deshabilitar interrupciones
    cli

    ; Cambiar modo de video a 80 X 50
    mov ax, 0003h
    int 10h ; set mode 03h
    xor bx, bx
    mov ax, 1112h
    int 10h ; load 8x8 font

    ; Imprimir mensaje de bienvenida
    imprimir_texto_mr iniciando_mr_msg, iniciando_mr_len, 0x07, 0, 0
    

    ; Habilitar A20
    call habilitar_A20
    cli

    ; Cargar la GDT
    LGDT [GDT_DESC]
    
    ; Setear el bit PE del registro CR0
    mov EAX, CR0
    or EAX, 1
    mov CR0, EAX

    ; Saltar a modo protegido
    jmp 0x48:modo_protegido ; 0100 1 | 0 | 00

    BITS 32
    modo_protegido:

    ; Establecer selectores de segmentos
    xor EAX, EAX 
    mov AX, 0x58    ;0101 1000 ; cargo el selector de segmento de datos level 0: 11|0|00
    mov DS, AX
    mov ES, AX
    mov GS, AX
    mov SS, AX

    mov AX, 0x68 ; 0110 1000 ; cargo el selector de segmento de video 13 | 0 | 00
    mov FS, AX

    ; Establecer la base de la pila
    mov EBP, 0x27000
    mov ESP, EBP

    ; Imprimir mensaje de bienvenida
    imprimir_texto_mp iniciando_mp_msg, iniciando_mp_len, 0x07, 2, 0

    ; Inicializar pantalla
    call limpiar_pantalla
    call pantalla_juego
    imprimir_texto_mp equipo_mp_msg, equipo_mp_len, 0x07, 0, 53
    
    ; Inicializar el manejador de memoria
    
    ; Inicializar el directorio de paginas
    call mmu_inicializar
    ; Cargar directorio de paginas
    
    ; Habilitar paginacion
    mov eax, MAINPAGEDIR
    mov cr3, eax
    mov eax, cr0
    or eax, 0x80000000
    mov cr0, eax


    ; Inicializar tss
    call gdt_set_tss ; primero inicializo las entradas de la gdt de las tsss
    call tss_inicializar
    
    
    ; Inicializar tss de la tarea Idle
    
    ; Inicializar tss de las tanques
    
    ; Inicializar el scheduler
        call sched_inicializar
    ; Inicializar la IDT
        call idt_inicializar
    

    ; Inicializar Game
        call game_inicializar
    ; Cargar IDT
    lidt [IDT_DESC]
    ; Configurar controlador de interrupciones
    
    ; pintar posiciones inciales de tanques
    
    ; Cargar tarea inicial
 ;               0000 1110   000
    mov ax, 0x70 ; GDT_IDX_TAREA_INICIAL ; 0x0E * 8 = 0111 0000 = 0x70
    ltr ax

    ; Habilitar interrupciones
    call deshabilitar_pic
    call resetear_pic
    call habilitar_pic
    sti ; habilitamos interrupciones
  
    ; Saltar a la primera tarea: Idle
    jmp 0x78:0x0 ; GDT_IDX_TAREA_1  ;0x0F * 8 = 0111 1000 

    ; Ciclar infinitamente (por si algo sale mal...)
    mov eax, 0xFFFF
    mov ebx, 0xFFFF
    mov ecx, 0xFFFF
    mov edx, 0xFFFF
    jmp $
    jmp $

;; -------------------------------------------------------------------------- ;;

%include "a20.asm"
