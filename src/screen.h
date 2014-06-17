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
#define ASCII_first_num			48
#define ASCII_first_let			65

typedef struct video_elem {
	unsigned char ascii, modo;
} __attribute__((packed)) video_elem;
typedef struct str_estado_de_tarea{
	int eax; int ebx; int ecx; int edx; int esi; 
	int edi; int ebp; int esp; int eip; int cr0; int cr2; int cr3 ;
	int cs; int ds; int es; int fs; int gs; int ss; int eflags;
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
