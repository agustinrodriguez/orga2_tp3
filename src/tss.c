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
	limpiar_tss(&tss_inicial);
    tss_inicializar_tarea_idle();
    tss_inicializar_tareas_tanques();
}

void tss_inicializar_tarea_idle() {
    definir_tss(&tss_idle, MAINPAGEDIR,PILA_KERNEL,EIP_IDLE, 0, PILA_KERNEL);
    tss_next_1 = tss_idle;
    tss_next_2 = tss_idle;
}

void tss_inicializar_tareas_tanques() {
    unsigned int cr3_tarea;
    int i;

    for (i = 0; i < CANT_TANQUES; i++) {
        cr3_tarea = mmu_inicializar_dir_tarea(i + 1);
        unsigned int pila_tarea;
        pila_tarea = dame_pagina_libre() + 4096;
        tss_inicializar_tareas_tanque(i, cr3_tarea, pila_tarea);
    }
}

void tss_inicializar_tareas_tanque(int num_tanque, unsigned int cr3_tarea, unsigned int pila_tarea) {
    definir_tss(&tss_tanques[num_tanque],cr3_tarea,pila_tarea, 0x08000000, (unsigned int) 3, (unsigned int) 0x08002000);

}

void limpiar_tss(tss * task) {
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

        .eflags = 0x00000202,
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


void definir_tss(tss *task, unsigned int cr3, unsigned int esp0, unsigned int eip, unsigned int us, unsigned int pila){
    task->cr3 = cr3;
    task->eip = eip;
    task->esp0 = esp0;

    
    task->ss0 = GDT_IDX_DATA_0 << 3;
    task->esp = pila;
    task->ebp = task->esp;
    task->eflags = 0x00000202;
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

    task->cs = Codigo;
    task->ds = Datos;
    task->fs = Datos;
    task->es = Datos;
    task->gs = Datos;
    task->ss = Datos; 
};

tss dame_tss(unsigned int tanque){
    return tss_tanques[tanque];
}