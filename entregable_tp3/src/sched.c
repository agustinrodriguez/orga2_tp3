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
		tss_next_2 = sched.tareas[tarea_siguiente()].tarea;
	} else {
		sched.tss_actual = 1;
		indice_gdt = GDT_IDX_TAREA_1 << 3;
		sched.tareas[sched.tarea_anterior].tarea = tss_next_1;
		tss_next_1 = sched.tareas[tarea_siguiente()].tarea;
	}

	sched.tarea_anterior = sched.tarea_actual;
	sched.tarea_actual = tarea_siguiente();
	sched.quantum_restante = sched.tarea_actual;

	return indice_gdt;
}

int tarea_siguiente() {
	int i = sched.quantum_restante + 1;
	while (i != sched.tarea_actual) {
		if (i == CANT_TAREAS +1){
			i = 1;
		} else {
			if (sched.tareas[i].estado == 1) {
				return i;
			}

			i++;
		}
	}
	if (sched.tareas[sched.tarea_actual].estado == 1) {
		return sched.tarea_actual;
	}
	return 0;
}

void sched_inicializar() {
    int i;
	sched.tareas[0].tarea = tss_idle;
	sched.tareas[0].estado = 1;
	sched.tareas[0].indice = 0;
	sched.tareas[0].desalojo = 255;

    for (i = 1; i < CANT_TAREAS; i++) {
		sched.tareas[i].tarea = tss_tanques[i - 1];
		sched.tareas[i].estado = 1;
		sched.tareas[i].indice = i;
		sched.tareas[i].desalojo = 255;
    }

    sched.quantum_restante = 0;
    sched.tarea_actual = 0; // idle
    sched.tarea_anterior = 0; // idle
    sched.tss_actual = 1; // esto es 1 o 2
    sched.pause = 0;
}

void desalojar_tarea() {
	sched.tareas[sched.tarea_actual].estado = 0;
	//sched_proximo_idle();
}

unsigned short sched_proximo_idle() {
	unsigned short indice_gdt;
	if (sched.tss_actual == 1) {
		sched.tss_actual = 2;
		indice_gdt = GDT_IDX_TAREA_2 << 3;
		sched.tareas[sched.tarea_anterior].tarea = tss_next_2;
		tss_next_2 = sched.tareas[0].tarea;
	} else {
		sched.tss_actual = 1;
		indice_gdt = GDT_IDX_TAREA_1 << 3;
		sched.tareas[sched.tarea_anterior].tarea = tss_next_1;
		tss_next_1 = sched.tareas[0].tarea;
	}

	sched.tarea_anterior = sched.tarea_actual;
	sched.tarea_actual = 0;
	return indice_gdt;
}

void matar_tarea_actual() {
	sched.tareas[sched.tarea_actual].estado = 0;
	if (sched.tarea_actual == CANT_TAREAS)	{
		sched.quantum_restante = 0;
	}else{
		sched.quantum_restante = sched.tarea_actual;
	}
	//sched_proximo_idle();
}

unsigned int dame_actual(){
	return sched.tarea_actual;
}

void cambiar_estado(unsigned int estado){
	sched.pause = estado;
}

unsigned int dame_estado(){
	return sched.pause;
}

void guardar_desalojo(unsigned int desalojo){
	sched.tareas[sched.tarea_actual-1].desalojo = desalojo;
}

unsigned int dame_desalojo(unsigned int id){
	return sched.tareas[id-1].desalojo;
}