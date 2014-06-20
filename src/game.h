/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
*/

#ifndef __GAME_H__
#define __GAME_H__

#include "mmu.h"
#include "screen.h"
#include "defines.h"


typedef enum direccion_e { NE = 12, N  = 11, NO = 14,
                           E  = 22, C  = 0,  O  = 44,
                           SE = 32, S  = 33, SO = 34 } direccion;


void game_inicializar();

unsigned int game_mover(unsigned int id, direccion d);

unsigned int game_misil(unsigned int id, int val_x, int val_y, unsigned int misil, unsigned int size);

unsigned int game_minar(unsigned int id, direccion d);

unsigned int game_celda_minada(int fil, int col);

unsigned char dame_pos_inicial_fila(int id);

unsigned char dame_pos_inicial_col(int id);

unsigned int game_celda_vacia(int fil, int col);

unsigned int game_celda_minada(int fil, int col);

unsigned int game_posicion_en_rango(int fil, int col);

void inicializar_tanque(unsigned int id, unsigned int fila, unsigned int col);

#endif  /* !__GAME_H__ */
