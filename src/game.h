/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
*/

#ifndef __GAME_H__
#define __GAME_H__

#include "mmu.h"
#include "sched.h"
#include "tss.h"
#include "screen.h"
#include "defines.h"

#define TABLERO_FILS 		50
#define TABLERO_COLS 		50
#define TABLERO_CELDA_VACIA 0xFF
#define TABLERO_CELDA_MINADA 0xCA

//JUGADORES
#define JUG_1 				1
#define JUG_2 				2
#define JUG_3 				3
#define JUG_4 				4
#define JUG_5 				5
#define JUG_6 				6
#define JUG_7 				7
#define JUG_8 				8

/* Posiciones iniciales de los jugadores */
#define JUG1_FIL_INIT 		0
#define JUG1_COL_INIT 		0

#define JUG2_FIL_INIT 		0
#define JUG2_COL_INIT 		(TABLERO_COLS-1)

#define JUG3_FIL_INIT 		(TABLERO_FILS-1)
#define JUG3_COL_INIT 		(TABLERO_COLS-1)

#define JUG4_FIL_INIT 		(TABLERO_FILS-1)
#define JUG4_COL_INIT 		0

#define JUG5_FIL_INIT 		20
#define JUG5_COL_INIT 		20

#define JUG6_FIL_INIT 		20
#define JUG6_COL_INIT 		30

#define JUG7_FIL_INIT 		30
#define JUG7_COL_INIT 		20

#define JUG8_FIL_INIT 		30
#define JUG8_COL_INIT 		30


typedef enum direccion_e { NE = 12, N  = 11, NO = 14,
                           E  = 22, C  = 0,  O  = 44,
                           SE = 32, S  = 33, SO = 34 } direccion;


void game_inicializar();

unsigned int game_mover(unsigned int id, direccion d);

unsigned int game_misil(unsigned int id, int val_x, int val_y, unsigned int misil, unsigned int size);

unsigned int game_minar(unsigned int id, direccion d);

unsigned int game_celda_minada(int fil, int col);

unsigned char dame_pos_fila(unsigned char id);

unsigned char dame_pos_col(unsigned char id);

unsigned int game_celda_vacia(int fil, int col);

unsigned int game_celda_minada(int fil, int col);

unsigned int game_posicion_en_rango(int fil, int col);

#endif  /* !__GAME_H__ */
