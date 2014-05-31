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
	video_elem *elemento;

	for (fila = 0; fila < VIDEO_FILS; fila++) {
		for (col = 0; col < VIDEO_COLS; col++) {
			//C_FG_GREEN
			elemento = (video_elem *) mem_video;
			elemento->modo = (unsigned char) 0x20; //00100000b;
			elemento->ascii = (unsigned char) 0x00; // caracter nulo
			mem_video = mem_video + 2;
		}
	}
}


