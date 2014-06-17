/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#include "sched.h"

unsigned short sched_proximo_indice() {
	unsigned short indice_gdt;

	if (sched.tss_actual == 1) {
		sched.tss_actual = 2;
		indice_gdt = GDT_IDX_TAREA_2 << 3;
		sched.tareas[sched.tarea_anterior].tarea = tss_next_2;
		tss_next_2 = tarea_siguiente();
	} else {
		sched.tss_actual = 1;
		indice_gdt = GDT_IDX_TAREA_1 << 3;
		sched.tareas[sched.tarea_anterior].tarea = tss_next_1;
		tss_next_1 = tarea_siguiente();
	}

	sched.tarea_anterior = sched.tarea_actual;
	sched.tarea_actual = tarea_siguiente().indice;
	sched.quantum_restante = 0;

	return indice_gdt;
}

tarea_t tarea_siguiente() {
	int i = sched.tarea_actual + 1;
	while (i != sched.tarea_actual) {
		if (i == CANT_TAREAS + 1){
			i = 1;
		} else {
			if (sched.tareas[i].estado == 1){
				return sched.tareas[i];
			}

			i++;
		}
	}

	if (sched.tareas[sched.tarea_actual].estado == 1) {
		return sched.tareas[sched.tarea_actual];
	}

	return sched.tareas[0];
}

void sched_inicializar() {
    int i;
	sched.tareas[0].tarea = tss_idle;
	sched.tareas[0].estado = 1;
	sched.tareas[0].indice = 0;

    for (i = 1; i < CANT_TAREAS + 1; i++) {
		sched.tareas[i].tarea = tss_tanques[i];
		sched.tareas[i].estado = 1;
		sched.tareas[i].indice = i;
    }

    sched.quantum_restante = 0;
    sched.tarea_actual = 0; // idle
    sched.tarea_anterior = 0; // idle
    sched.tss_actual = 1; // esto es 1 o 2
}

void desalojar_tarea() {
	sched.tareas[sched.tarea_actual].estado = 0;
	sched_proximo_idle();
}

unsigned short sched_proximo_idle() {
	unsigned short indice_gdt;

	if (sched.tss_actual == 1) {
		sched.tss_actual = 2;
		indice_gdt = GDT_IDX_TAREA_2 << 3;
		sched.tareas[sched.tarea_anterior].tarea = tss_next_2;
		tss_next_2 = sched.tareas[0];
	} else {
		sched.tss_actual = 1;
		indice_gdt = GDT_IDX_TAREA_1 << 3;
		sched.tareas[sched.tarea_anterior].tarea = tss_next_1;
		tss_next_1 = sched.tareas[0];
	}

	sched.tarea_anterior = sched.tarea_actual;
	sched.tarea_actual = 0;
	sched.quantum_restante = 0;

	return indice_gdt;
}