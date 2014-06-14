/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de estructuras para administrar tareas
*/

#include "tss.h"

tss tss_next_1;
tss tss_next_2;

tss tss_inicial;
tss tss_idle;

tss tss_tanques[CANT_TANQUES];

void tss_inicializar() {
	limpiar_para_interrumpir(&tss_inicial);
	definir_tss(&tss_idle, MAINPAGEDIR,PILA_KERNEL,EIP_IDLE,0,PILA_KERNEL);
}

void limpiar_para_interrumpir(tss * task){
	(* task) = (tss) {
    .unused0 = 0x0,
    .unused1 = 0x0,
    .unused2 = 0x0,
    .unused3 = 0x0,
    .unused4 = 0x0,
    .unused5 = 0x0,
    .unused6 = 0x0,
    .unused7 = 0x0,
    .unused8 = 0x0,
    .unused9 = 0x0,
    .unused10 = 0x0,

    .ptl = 0x0
    ,
    .esp0 = 0x0,    
    .esp1 = 0x0,
    .esp2 = 0x0,

    .ss0 = 0x0,
    .ss1 = 0x0,
    .ss2 = 0x0,
    
    .cr3 = 0x0,

    .eip = 0x0,

    .eflags = 0x00000202, //Esto no entendi bien, segun bombita en el chat me dijo q en este flag tengo q hacer lo de la interrupcion 52
    //osea a partir de aca cuando esto este activo se va a poder interrumpir
    // y segun el pocho la tarea inicial la puedo desalojar yo manualmente y no me importa lo q va a tener

    .eax = 0x0,
    .ecx = 0x0,
    .edx = 0x0,
    .ebx = 0x0,
    .esp = 0x0,
    .ebp = 0x0,
    .esi = 0x0,
    .edi = 0x0,

    .es = 0x0,
    .cs = 0x0,
    .ss = 0x0,
    .ds = 0x0,
	.fs = 0x0,
  
    .gs = 0x0,
    .ldt = 0x0,
   
    .dtrap = 0x0,
    .iomap = 0x0,
	};
};


void definir_tss(tss * task, unsigned int cr3, unsigned int esp0, unsigned int eip, unsigned int us, unsigned int pila){
    //Completo lo que dice en la diapos de manejo basico de tareas, lo q no se bien es los privilegios
    (*task).cr3 = cr3;
    (*task).eip = eip;
    (*task).esp0 = esp0;

    
    (*task).ss0 = GDT_IDX_DATA_0 << 3;
    (*task).esp = pila;//hay q darle el valor de pila, segun enunciado es la pila del kernel tengo entendido
    (*task).ebp = (*task).esp;

    //SELECTORES
    unsigned int Datos;
    unsigned int Codigo;
//en teoria segun como nos dijo marco, nos caen todas las tss nivel 0 por ende no haria falta este if

    if(us == 3){   
        Datos = (GDT_IDX_DATA_3 << 3) + 0x03; 
        Codigo = (GDT_IDX_CODE_3 << 3) + 0x03;
    }else{                  
        Datos = (GDT_IDX_DATA_0 << 3); 
        Codigo = (GDT_IDX_CODE_0 << 3);
    }

    (*task).cs = Codigo;
    (*task).ds = Datos;
    (*task).fs = Datos;
    (*task).es = Datos;
    (*task).gs = Datos;
    (*task).ss = Datos; 
};



