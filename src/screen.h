/** por compatibilidad se omiten tildes **
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
#define ASCII_first_num			48
#define ASCII_first_let			65

typedef struct video_elem {
	unsigned char ascii, modo;
} __attribute__((packed)) video_elem;
typedef struct str_estado_de_tarea{
	unsigned int * eax; unsigned int * ebx;  unsigned int * ecx;  unsigned int * edx;  unsigned int * esi; 
	 unsigned int * edi;  unsigned int * ebp;  unsigned int * esp;  unsigned int * eip;  unsigned int * cr0;  unsigned int * cr2;  unsigned int * cr3 ;
	 unsigned int * cs;  unsigned int * ds;  unsigned int * es;  unsigned int * fs;  unsigned int * gs;  unsigned int * ss;  unsigned int * eflags;
} __attribute__((__packed__)) estado_task;
estado_task estado_error;

void limpiar_pantalla();
void print_error(int error_code);
void imprimir_texto(char * mensaje, int len);
void pantalla_juego();
void imprimir_nombre_grupo();
void caracter_pintado();
void imprimir_numero_teclado(unsigned char tecla);
void imprimir_texto_para_tanques(char * mensaje, int len, int inicio);
void print_tablaerror();
char * convertir_a_string(int registro, char * txt, int inicio);

#endif  /* !__SCREEN_H__ */
