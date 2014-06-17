#ifndef __ESTRSCHED_H__
#define __ESTRSCHED_H__

#include "screen.h"
#include "tss.h"


/*Struct de cada tarea*/
struct tarea_t{
    tss tarea;       // TSS Segment Selector para la tarea.
    unsigned int estado;        // Estado: si el estado == 1 entonces puedo acceder a la tarea. Si estado == 0 la tarea fue desalojada.
    unsigned int indice;
};

/*Main struct del scheduler*/
struct sched_t{
    struct tarea_t tareas[CANT_TAREAS + 1]; // Esto tiene que contener una tarea por cada tarea que haya incluida la IDLE.
    unsigned int quantum_restante;          // QUANTUMS restantes
    unsigned int tarea_actual;              // Indice del array tareas que esta corriendo ahora.
    unsigned int tarea_anterior;            // Indice del array tareas que esta corriendo ahora.
    unsigned int idle_on;
    unsigned int tss_actual;
};

struct tarea_t tarea;
struct sched_t sched;

/*DESALOJAR_TAREA: Desaloja la tarea actual y salta a la tarea IDLE.*/

#endif	/* !__ESTRSCHED_H__ */
