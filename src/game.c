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

tanque_g tanques[CANT_TANQUES];

//unsigned char (*tablero)[TABLERO_COLS] = (unsigned char (*)[TABLERO_COLS]) 0x300000;
int tablero[TABLERO_FILS][TABLERO_COLS];
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

	// Inicialización de tanques (esto ya estaria mapeado)
	inicializar_tanque(TANQUE1, TANQUE1_FIL_INICIAL, TANQUE1_COL_INICIAL);
	inicializar_tanque(TANQUE2, TANQUE2_FIL_INICIAL, TANQUE2_COL_INICIAL);
	inicializar_tanque(TANQUE3, TANQUE3_FIL_INICIAL, TANQUE3_COL_INICIAL);
	inicializar_tanque(TANQUE4, TANQUE4_FIL_INICIAL, TANQUE4_COL_INICIAL);
	inicializar_tanque(TANQUE5, TANQUE5_FIL_INICIAL, TANQUE5_COL_INICIAL);
	inicializar_tanque(TANQUE6, TANQUE6_FIL_INICIAL, TANQUE6_COL_INICIAL);
	inicializar_tanque(TANQUE7, TANQUE7_FIL_INICIAL, TANQUE7_COL_INICIAL);
	inicializar_tanque(TANQUE8, TANQUE8_FIL_INICIAL, TANQUE8_COL_INICIAL);

}

void inicializar_tanque(unsigned int id, unsigned int fila, unsigned int col) {
    tanque_g *tanque_actual = &tanques[id - 1];
    int i, j;

    for (i = 0; i < TABLERO_FILS; i++) {
        for (j = 0; j < TABLERO_COLS; j++) {
            tanque_actual->camino[i][j] = 0;
        }
    }

	tablero[fila][col] = id;
    tanque_actual->id = id;
    tanque_actual->fila = fila;
    tanque_actual->col = col;
    tanque_actual->camino[fila][col] = id;
	pintar_tanque(tanque_actual, C_FG_LIGHT_GREY, C_FG_WHITE);

	tablero[fila][col + 1] = id;
    tanque_actual->fila = fila;
    tanque_actual->col = col + 1;
    tanque_actual->camino[fila][col + 1] = id;
    tanque_actual->dir_virtual = 0x08001000;
    pintar_tanque(tanque_actual, C_FG_LIGHT_GREY, C_FG_WHITE);
}

unsigned int game_mover(unsigned int id, direccion d) {
	tanque_g *tanque_actual = &tanques[id - 1];
    switch (d) {
        case N:
            tanque_actual->fila--;
            break;
        case NE:
            tanque_actual->fila--;
            tanque_actual->col++;
            break;
        case NO:
            tanque_actual->fila--;
            tanque_actual->col--;
            break;
        case E:
            tanque_actual->col++;
            break;
        case O:
            tanque_actual->col--;
            break;
        case SE:
            tanque_actual->fila++;
            tanque_actual->col++;
            break;
        case SO:
            tanque_actual->fila++;
            tanque_actual->col--;
            break;
        case S:
            tanque_actual->fila++;
            break;
        case C:
            break;
    }

    if (tanque_actual->fila < 0) {
    	tanque_actual->fila = TABLERO_FILS - 1;
    }

    if (tanque_actual->col < 0) {
    	tanque_actual->col = TABLERO_COLS - 1;
    }

    if (tanque_actual->fila == TABLERO_FILS) {
    	tanque_actual->fila = 0;
    }

    if (tanque_actual->col == TABLERO_COLS) {
    	tanque_actual->col = 0;
    }

    if (tanque_actual->camino[tanque_actual->fila][tanque_actual->col] != id) {
        tanque_actual->dir_virtual += 0x1000;
        mmu_mapear_pagina(tanque_actual->dir_virtual, get_cr3_task(id), 
            dame_fisica(tanque_actual->fila, tanque_actual->col), 1, 1, 1);
    }

    if (tablero[tanque_actual->fila][tanque_actual->col] == -1) {
    	guardar_desalojo(52);
        matar_tarea_actual();
    	pintar_tanque_destruido(tanque_actual);
        tablero[tanque_actual->fila][tanque_actual->col] = 0;
    } else {
	    if (tablero[tanque_actual->fila][tanque_actual->col] != id
	    	&& tablero[tanque_actual->fila][tanque_actual->col] != 0) {
			pintar_tanque_superpuesto(tanque_actual);
	    } else {
	    	pintar_tanque(tanque_actual, C_FG_LIGHT_GREY, C_FG_BLACK);
	    }
	    // en el tablero dejamos el ultimo tanque que paso
	    tablero[tanque_actual->fila][tanque_actual->col] = id;
    }


    return tanque_actual->dir_virtual;
}

unsigned int game_misil(unsigned int id, int val_x, int val_y, unsigned int misil, unsigned int size) {
    tanque_g *tanque_actual = &tanques[id - 1];
    unsigned int destino;
    int fila, columna;

    fila = tanque_actual->fila + val_y;
    columna = tanque_actual->col + val_x;
    if (fila < 0) {
        fila += 50;
    } else if (fila > 49) {
        fila -= 50; 
    }
    
    if (columna < 0) {
        columna += 50;
    } else if (columna > 49) {
        columna -= 50; 
    }

    if (tablero[fila][columna] == -1) {
        tablero[fila][columna] = 0;
    }

    pintar_misil(id, fila, columna);

    destino = dame_fisica(fila, columna);
    unsigned int misil_a_fisica = dame_fisica_de_virtual(misil,get_cr3_task(id));
    copiar_pagina_size(misil_a_fisica, destino, size);
    return TRUE;
}

unsigned int game_minar(unsigned int id, direccion d) {
	tanque_g *tanque_actual = &tanques[id - 1];
    switch (d) {
        case N:
        	tablero[tanque_actual->fila - 1][tanque_actual->col] = -1;
            break;
        case NE:
            tablero[tanque_actual->fila - 1][tanque_actual->col + 1] = -1;
            break;
        case NO:
            tablero[tanque_actual->fila - 1][tanque_actual->col - 1] = -1;
            break;
        case E:
            tablero[tanque_actual->fila][tanque_actual->col + 1] = -1;
            break;
        case O:
            tablero[tanque_actual->fila][tanque_actual->col - 1] = -1;
            break;
        case SE:
        	tablero[tanque_actual->fila + 1][tanque_actual->col + 1] = -1;
            break;
        case SO:
        	tablero[tanque_actual->fila + 1][tanque_actual->col - 1] = -1;
            break;
        case S:
            tablero[tanque_actual->fila + 1][tanque_actual->col] = -1;
            break;
        case C:
            break;
    }

    return TRUE;
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

void pintar_tanque(tanque_g *tanque, unsigned int color_fondo, unsigned int color_caracter) { 
	unsigned int pos_video;
	pos_video = pasaje_a_mapa_video(dame_fisica(tanque->fila, tanque->col));
	imprimir_en_mapa(tanque->id + 48, pos_video, color_fondo, color_caracter);
}

void pintar_tanque_superpuesto(tanque_g *tanque) {
	unsigned int pos_video;
	pos_video = pasaje_a_mapa_video(dame_fisica(tanque->fila, tanque->col));
	imprimir_en_mapa('x', pos_video, C_FG_BROWN, C_FG_BLACK);
}

void pintar_tanque_destruido(tanque_g *tanque) {
	unsigned int pos_video;
	pos_video = pasaje_a_mapa_video(dame_fisica(tanque->fila, tanque->col));
	imprimir_en_mapa(tanque->id + 48, pos_video, C_FG_RED, C_FG_WHITE);
}

void pintar_misil(unsigned int id, unsigned int fila, unsigned int columna) {
    unsigned int pos_video;
    pos_video = pasaje_a_mapa_video(dame_fisica(fila, columna));
    imprimir_en_mapa(id + 48, pos_video, C_FG_MAGENTA, C_FG_RED);
}