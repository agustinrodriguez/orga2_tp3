/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
*/

#include "game.h"

char campo_minado[CAMPO_SIZE][CAMPO_SIZE];

unsigned int game_celda_vacia(int fil, int col);
unsigned int game_posicion_en_rango(int fil, int col);

unsigned int MAPA_PAG_1[] = { 0, 0X00400000, 0X00402000, 
							0X00404000, 0X00406000, 0X00408000, 
							0X0040A000, 0X0040C000, 0X0040E000};

unsigned int MAPA_PAG_2[] = { 0, 0X00401000, 0X00403000, 
							0X00405000, 0X00407000, 0X00409000, 
							0X0040B000, 0X0040D000, 0X0040F000};


unsigned char (*tablero)[TABLERO_COLS] = (unsigned char (*)[TABLERO_COLS]) (TABLERO_ADDR);
unsigned char dame_pos_fila(unsigned char id);
unsigned char dame_pos_col(unsigned char id);
void game_inicializar() {
	int f;
	int c;

	// Inicialización de celdas
	for(f = 0; f < TABLERO_FILS; f++) {
		for(c = 0; c < TABLERO_COLS; c++) {
			tablero[f][c] = TABLERO_CELDA_VACIA;
		}
	}

	// Inicialización de jugadores
	tablero[JUG1_FIL_INIT][JUG1_COL_INIT] = JUG_1;
	tablero[JUG2_FIL_INIT][JUG2_COL_INIT] = JUG_2;
	tablero[JUG3_FIL_INIT][JUG3_COL_INIT] = JUG_3;
	tablero[JUG4_FIL_INIT][JUG4_COL_INIT] = JUG_4;
	tablero[JUG4_FIL_INIT][JUG4_COL_INIT] = JUG_5;	
	tablero[JUG4_FIL_INIT][JUG4_COL_INIT] = JUG_6;
	tablero[JUG4_FIL_INIT][JUG4_COL_INIT] = JUG_7;
	tablero[JUG4_FIL_INIT][JUG4_COL_INIT] = JUG_8;

	//char * tanque= " ";
	/*int i;
	for (i = 1; i < 9; ++i)
	{	
		//convertir_a_string(i,tanque);
		caracter_pintado(i+48,pasaje_a_mapa(MAPA_PAG_1[i]));
		caracter_pintado(i+48,pasaje_a_mapa(MAPA_PAG_2[i]));
	}*/
	
}

unsigned int game_mover(unsigned int id, direccion d) {
    unsigned char i = dame_pos_fila(id);
    unsigned char j = dame_pos_col(id);
    if(d == NE){
    	i--;
    	j--;
    }
    if(d == NO){
    	i--;
    	j++;
    }
    if(d == SE){
    	i++;
    	j--;
    }
    if(d == SO){
    	i++;
    	j++;
    }
    if(d == O) j++;
    if(d == E) j--;
    if(d == N) i--;
    if(d == S) j++;
    if(d == C) return TRUE;    
    if(game_posicion_en_rango(i, j)){
    	if(game_celda_minada(i, j)){
    		//desalojar_tarea();
    		tablero[i][j] = TABLERO_CELDA_VACIA;
    		return FALSE;
    	}
    	tablero[i][j] = id;
    	unsigned int pagina = dame_pagina_libre();
    	mmu_mapear_pagina(pagina, tss_get_cr3(id), tablero[i][j], 1, 1, 1);
    	return TRUE;
    }
    return FALSE;
}

unsigned int game_misil(unsigned int id, int val_x, int val_y, unsigned int misil, unsigned int size) {
    return TRUE;
}

unsigned int game_minar(unsigned int id, direccion d) {
    unsigned char i = dame_pos_fila(id);
    unsigned char j = dame_pos_col(id);
    if(d == NE){
    	i--;
    	j--;
    }
    if(d == NO){
    	i--;
    	j++;
    }
    if(d == SE){
    	i++;
    	j--;
    }
    if(d == SO){
    	i++;
    	j++;
    }
    if(d == O) j++;
    if(d == E) j--;
    if(d == N) i--;
    if(d == S) j++;
    if(game_posicion_en_rango(i, j)){
    	tablero[i][j] = TABLERO_CELDA_MINADA;
    return TRUE;
    }
    return FALSE;
}

unsigned int game_celda_minada(int fil, int col) {
	if (tablero[fil][col] == TABLERO_CELDA_MINADA) {
		return TRUE;
	} else {
		return FALSE;
	}
}

unsigned int game_celda_vacia(int fil, int col) {
	if (tablero[fil][col] == TABLERO_CELDA_VACIA) {
		return TRUE;
	} else {
		return FALSE;
	}
}

unsigned int game_posicion_en_rango(int fil, int col) {
	if (0 <= fil && fil < TABLERO_FILS &&
		0 <= col && col < TABLERO_COLS) {
		return TRUE;
	} else {
		return FALSE;
	}
}
//4194304  -- 14434303 

/*
b8000

0X00400000 = b8000

4194304 == 753664

4210688 = 1028 
0X00404000 = b8002



unsigned int pasaje_a_mapa(int direccion){
	int i = direccion - 0X00400000;
	i = i/4096;
	i = i*2;
	i = i + 0xb8000;
	return i;
}


*/


unsigned char dame_pos_fila(unsigned char id){
	unsigned char res;
	if(id == 1)   res = JUG1_FIL_INIT;
	if(id == 2)   res = JUG2_FIL_INIT;
	if(id == 3)   res = JUG3_FIL_INIT;
	if(id == 4)   res = JUG4_FIL_INIT;
	if(id == 5)   res = JUG5_FIL_INIT;
	if(id == 6)   res = JUG6_FIL_INIT;
	if(id == 7)   res = JUG7_FIL_INIT;
	if(id == 8)   res = JUG8_FIL_INIT;
	return res;
}

unsigned char dame_pos_col(unsigned char id){
	unsigned char res;
	if(id == 1) res = JUG1_COL_INIT;
	if(id == 2) res = JUG2_COL_INIT;
	if(id == 3) res = JUG3_COL_INIT;
	if(id == 4) res = JUG4_COL_INIT;
	if(id == 5) res = JUG5_COL_INIT;
	if(id == 6) res = JUG6_COL_INIT;
	if(id == 7) res = JUG8_COL_INIT;
	return res;
}
