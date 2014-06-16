/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#include "sched.h"

//unsigned int indices_tareas = {GDT_IDX_TAREA_1,GDT_IDX_TAREA_2,GDT_IDX_TAREA_1,GDT_IDX_TAREA_2,
//	GDT_IDX_TAREA_1,GDT_IDX_TAREA_2,GDT_IDX_TAREA_1,GDT_IDX_TAREA_2};
//segun el enunciado se pide q 1)tss1 ..2)tss2 y asi intercalado CHEQUEAR ESTO

/*unsigned short sched_proximo_indice() {
  return 0;
}

void sched_inicializar(){
	struct tarea_t tarea_idle;
	tarea_idle.tarea = (GDT_IDX_TAREA_1 << 3);
	tarea_idle.estado = 1;
	tarea_idle.indice = 0;
	sched.tareas[0] = tarea_idle;

	int i;
	for (i = 0; i < CANT_TAREAS; i++) 
	{
		struct tarea_t tarea_struct;
		tarea_struct.tarea = (indices_tareas[i] << 3);
		tarea_struct.estado = 1;
		tarea_struct.indice = i + 1;
		sched.tareas[i + 1] = tarea_struct;
	}
	sched.QUANTUM_RESTANTE = QUANTUM_TAREA + 1;
	sched.TAREA_ACTUAL = 0;
	sched.CONTEXTO = 0;
	sched.TASKS_UP = CANT_TAREAS;
}

void desalojar_tarea(int tarea){
	sched.tareas[tarea].estado = 0;
	sched.TASKS_UP--;
	//faltaria hacer una funcion q muestre porq exploto
}*/
