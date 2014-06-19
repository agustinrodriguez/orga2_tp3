/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#ifndef __SCHED_H__
#define __SCHED_H__

#include "screen.h"
#include "tss.h"


/*Struct de cada tarea*/
typedef struct tarea_t{
    tss tarea;       // TSS Segment Selector para la tarea.
    unsigned int estado;        // Estado: si el estado == 1 entonces puedo acceder a la tarea. Si estado == 0 la tarea fue desalojada.
    unsigned int indice;
} tarea_;

/*Main struct del scheduler*/
typedef struct sched_t{
    struct tarea_t tareas[CANT_TAREAS + 1]; // Esto tiene que contener una tarea por cada tarea que haya incluida la IDLE.
    unsigned int quantum_restante;          // QUANTUMS restantes
    unsigned int tarea_actual;              // Indice del array tareas que esta corriendo ahora.
    unsigned int tarea_anterior;            // Indice del array tareas que esta corriendo ahora.
    unsigned int idle_on;
    unsigned int tss_actual;
} sched_;

struct tarea_t tarea;
struct sched_t sched;

/*DESALOJAR_TAREA: Desaloja la tarea actual y salta a la tarea IDLE.*/
void desalojar_tarea();

unsigned short sched_proximo_indice();
unsigned short sched_proximo_idle();
void sched_inicializar();
int tarea_siguiente();
void matar_tarea_actual();
#endif	/* !__SCHED_H__ */
