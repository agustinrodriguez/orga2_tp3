/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#include "screen.h"

void limpiar_pantalla() {
	int fila, col;
	unsigned char *mem_video = (unsigned char *) VIDEO_BASE; 

	for (fila = 0; fila < VIDEO_FILS * 2; fila++) {
		for (col = 0; col < VIDEO_COLS * 2; col++) {
			//C_FG_GREEN
			*mem_video = 0x20;//00100000b;
			mem_video++;
		}
	}
}


