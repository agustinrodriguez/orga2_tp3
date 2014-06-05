/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#ifndef __SCREEN_H__
#define __SCREEN_H__

#include "colors.h"
/* Definicion de la pantalla */
#define VIDEO_FILS 50
#define VIDEO_COLS 80
#define VIDEO_BASE 0xb8000

typedef struct video_elem {
	unsigned char ascii, modo;
} __attribute__((packed)) video_elem;

void limpiar_pantalla();
void print_error(int error_code);
void imprimir_texto(char * mensaje, int len);
void pantalla_juego();
void imprimir_nombre_grupo();

#endif  /* !__SCREEN_H__ */
