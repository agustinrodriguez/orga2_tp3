/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
*/

#include "game.h"

char campo_minado[CAMPO_SIZE][CAMPO_SIZE];

unsigned int MAPA_PAG_1[] = { 0, 0X00400000, 0X00402000, 
							0X00404000, 0X00406000, 0X00408000, 
							0X0040A000, 0X0040C000, 0X0040E000};

unsigned int MAPA_PAG_2[] = { 0, 0X00401000, 0X00403000, 
							0X00405000, 0X00407000, 0X00409000, 
							0X0040B000, 0X0040D000, 0X0040F000};


void game_inicializar() {
	//char * tanque= " ";
	int i;
	for (i = 1; i < 9; ++i)
	{	
		//convertir_a_string(i,tanque);
		caracter_pintado(i+48,pasaje_a_mapa(MAPA_PAG_1[i]));
		caracter_pintado(i+48,pasaje_a_mapa(MAPA_PAG_2[i]));
	}
	
}

unsigned int game_mover(unsigned int id, direccion d) {
    return TRUE;
}

unsigned int game_misil(unsigned int id, int val_x, int val_y, unsigned int misil, unsigned int size) {
    return TRUE;
}

unsigned int game_minar(unsigned int id, direccion d) {
    return TRUE;
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





