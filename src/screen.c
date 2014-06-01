/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#include "screen.h"

void limpiar_pantalla() {
	int fila, col, modo = 0;
	unsigned char *mem_video = (unsigned char *) VIDEO_BASE;
	video_elem *elemento;

	modo = modo + C_FG_GREEN * 16; // asigno el color de fondo verde al modo

	for (fila = 0; fila < VIDEO_FILS; fila++) {
		for (col = 0; col < VIDEO_COLS; col++) {
			elemento = (video_elem *) mem_video;
			elemento->modo = (unsigned char) modo; //00100000b (verde);
			elemento->ascii = (unsigned char) 0; // caracter nulo
			mem_video = mem_video + 2;
		}
	}
}


