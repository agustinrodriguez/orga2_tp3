/** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#ifndef __SCREEN_H__
#define __SCREEN_H__

#include "colors.h"
#include "sched.h"
#include "tss.h"
/* Definicion de la pantalla */
#define VIDEO_FILS 50
#define VIDEO_COLS 80
#define VIDEO_BASE 0xb8000
#define ASCII_first_num			48
#define ASCII_first_let			65

typedef struct video_elem {
	unsigned char ascii, modo;
} __attribute__((packed)) video_elem;

typedef struct str_estado_de_tarea {
	unsigned int eax; unsigned int ebx;  unsigned int ecx;  unsigned int edx;  unsigned int esi; 
	unsigned int edi;  unsigned int ebp;  unsigned int esp;  unsigned int eip;  unsigned int cr0;  unsigned int cr2;  unsigned int cr3 ;
	unsigned int cs;  unsigned int ds;  unsigned int es;  unsigned int fs;  unsigned int gs; 
	 unsigned int ss;  unsigned int eflags; unsigned int stack_0; unsigned int stack_1; unsigned int stack_2;
	 unsigned int stack_3; unsigned int stack_4;
} __attribute__((__packed__)) estado_task;
estado_task estado_error;

void limpiar_pantalla();
void imprimir_texto_para_tanques2(char * mensaje, int len, int inicio, char color);
void print_error(int error_code);
void imprimir_texto(char * mensaje, int len);
void pantalla_juego();
void imprimir_nombre_grupo();
void imprimir_en_mapa(unsigned int tanque, int lugar, unsigned int color_fondo, unsigned int color_caracter);
void imprimir_numero_teclado(unsigned char tecla);
void imprimir_texto_para_tanques(char * mensaje, int len, int inicio, char color);
void print_tablaerror(unsigned int tanque);
void convertir_a_string(unsigned int valor, char * cadena);
void imprimir_desalojo(unsigned int error);
unsigned int pasaje_a_mapa_video(int direccion);
void imprimir_reloj_tanque(int reloj);
void imprimo_tss(unsigned int tanque);

#endif  /* !__SCREEN_H__ */
