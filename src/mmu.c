/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del manejador de memoria
*/

#include "mmu.h"

unsigned int TASK_CR3[] = { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};

unsigned int TASK_CODE_SRC[] = {
	TASK_1_CODE_ADDR,
	TASK_2_CODE_ADDR,
	TASK_3_CODE_ADDR,
	TASK_4_CODE_ADDR,
	TASK_5_CODE_ADDR,
	TASK_6_CODE_ADDR,
	TASK_7_CODE_ADDR,
	TASK_8_CODE_ADDR
};

unsigned int TASK_PAG_3[] = { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};

unsigned int MEMORIA_RESTANTE = SECTORFREEMEM;

void mmu_inicializar() {
	//int i;
	mmu_inicializar_dir_kernel();

	/*for (i = 1; i < CANT_TAREAS + 1; i++) {
		mmu_inicializar_dir_tarea(i);
	}*/
}

unsigned int get_cr3_task(unsigned int id) {
	return TASK_CR3[id];
}
/*
INICIO AREA LIBRE 0x100000 == 1048576
FIN AREA LIBRE 0x3FFFFF == 4194303

TOTAL: 3145728 bytes
EN 4096 = 768 directorios o tablas?

DC3FFF



*/
void mmu_inicializar_dir_kernel() {
	int i;
	TASK_CR3[0] = MAINPAGEDIR;
	page_directory_entry * page_dir = (page_directory_entry *) MAINPAGEDIR;
	page_table_entry * page_table1 = (page_table_entry *) FIRSTPAGETABLE;
	page_table_entry * page_table2 = (page_table_entry *) SECONDPAGETABLE;
	page_table_entry * page_table3 = (page_table_entry *) TRHEEPAGETABLE;
	page_table_entry * page_table4 = (page_table_entry *) FOURPAGETABLE;

	unsigned char present = 0x01, rw = 0x01, us = 0x00;

	define_page_directory_entry(&page_dir[0], present, rw, us, (unsigned int) page_table1);
	define_page_directory_entry(&page_dir[1], present, rw, us, (unsigned int) page_table2);
	define_page_directory_entry(&page_dir[2], present, rw, us, (unsigned int) page_table3);
	define_page_directory_entry(&page_dir[3], present, rw, us, (unsigned int) page_table4);

	for (i = 4; i < 1024; i++) {
		define_page_directory_entry(&page_dir[i], 0, rw, us, 0);
	}
	
	for (i = 0; i < 1024; i++) {
		define_page_table_entry(&page_table1[i], present, rw, us, i * 4096);
		define_page_table_entry(&page_table2[i], present, rw, us, (1024 * 4096) + i * 4096);
		define_page_table_entry(&page_table3[i], present, rw, us, (2 * 1024 * 4096) + i * 4096);
	}

	// 452 entradas presentes en la tabla 4
	for (i = 0; i < 452; i++) {
		define_page_table_entry(&page_table4[i], present, rw, us, (3 * 1024 * 4096) + i * 4096);
	}

	// el resto no presentes
	for (i = 452; i < 1024; i++) {
		define_page_table_entry(&page_table4[i], 0, rw, us, (3 * 1024 * 4096) + i * 4096);
	}
	/*0x00000000 a 0x00DC3FFF
	14434303 bytes = 3 m y 11288575 bytes
	14.434.304 bytes = 
 
 	1 tabla tiene = 4194304 bytes
	
	1851392bytes esto divido 4k osea 1 bloque = 452 REDONDO!


 	0,44140625

1 pt -> 4 m

14434303 bytes -> aprox 14 m -> 4 pt

1 mega -> 1048576 bytes
3 mega -> 3145728 bytes
*/
}

/* INICIO MAPA 0X400000 == 4194304
FIN MAPA 0XDC3FFF == 14434303

total =  10240000 bytes

9 megas y 0,765625
784 k = 196 paginas

*/
unsigned int mmu_inicializar_dir_tarea(int num_tarea) {
	unsigned char rw;
	unsigned char us;
	unsigned char present;
	int j = 0;

	rw = 1;
	us = 0;
	present = 1;

	page_directory_entry * pdir = (page_directory_entry *) MEMORIA_RESTANTE;
	
	for (j = 0; j < 1024; j++) {
		null_pagedir_entry(&pdir[j]);
	}
	
	TASK_CR3[num_tarea] = MEMORIA_RESTANTE;
	page_table_entry * page_table1 = (page_table_entry *) FIRSTPAGETABLE;
	page_table_entry * page_table2 = (page_table_entry *) SECONDPAGETABLE;
	page_table_entry * page_table3 = (page_table_entry *) TRHEEPAGETABLE;
	page_table_entry * page_table4 = (page_table_entry *) FOURPAGETABLE;
	MEMORIA_RESTANTE += TAMANO_PAGINA;

	define_page_directory_entry(&pdir[0], present, rw, us, (unsigned int) page_table1);
	define_page_directory_entry(&pdir[1], present, rw, us, (unsigned int) page_table2);
	define_page_directory_entry(&pdir[2], present, rw, us, (unsigned int) page_table3);
	define_page_directory_entry(&pdir[3], present, rw, us, (unsigned int) page_table4);

	unsigned int codigo_tarea_pag_1 = TASK_CODE_SRC[num_tarea-1];
	unsigned int codigo_tarea_pag_2 = TASK_CODE_SRC[num_tarea-1] + 0x1000;
	/*unsigned int mapa_pag_1 = TASK_PAG_1[num_tarea];
	unsigned int mapa_pag_2 = TASK_PAG_2[num_tarea];*/
	unsigned int mapa_pag_1 = dame_direccion_mapa(num_tarea);
	unsigned int mapa_pag_2 = mapa_pag_1 + 0x1000;


	copiar_pagina(codigo_tarea_pag_1, mapa_pag_1);
	copiar_pagina(codigo_tarea_pag_2, mapa_pag_2);

	rw = 1;
	us = 1;
	present = 1;

	mmu_mapear_pagina(0x08000000, TASK_CR3[num_tarea], mapa_pag_1, present, rw, us);
	mmu_mapear_pagina(0x08001000, TASK_CR3[num_tarea], mapa_pag_2, present, rw, us);

	return TASK_CR3[num_tarea];
}

unsigned int dame_direccion_mapa(int num_tarea) {
	return dame_fisica(dame_pos_inicial_fila(num_tarea), dame_pos_inicial_col(num_tarea));
}

void define_page_directory_entry(page_directory_entry * directorio, 
	unsigned char present, unsigned char rw, unsigned char us, unsigned int base) {
		directorio->p = present;
		directorio->rw = rw;
		directorio->us = us;
		directorio->pwt = 0x00;
		directorio->pcd = 0x00;
		directorio->a = 0x00;
		directorio->ignored = 0x00;
		directorio->ps = 0x00;
		directorio->g = 0x00;
		directorio->available = 0x00;
		directorio->base_12_31 = base >> 12;
}

void define_page_table_entry(page_table_entry * tabla, 
	unsigned char present, unsigned char rw, unsigned char us, unsigned int base) {
		tabla->p = present;
		tabla->rw = rw;
		tabla->us = us;
		tabla->pwt = 0x00;
		tabla->pcd = 0x00;
		tabla->a = 0x00;
		tabla->d = 0x00;
		tabla->pat = 0x00;
		tabla->g = 0x00;
		tabla->available = 0x00;
		tabla->base_12_31 = base >> 12;
}


/*
0x08000000
0000 1000 00 | 00 0000 0000 | 0000 0000 0000

pde = cr3 + 0000 1000 00

pte = pde->base + 00 0000 0000

0000 1000 00 | 00 0000 0000

0x08001000

0000 1000 00 | 00 0000 0001 | 0000 0000 0000

0x08001000

*/
void mmu_mapear_pagina(unsigned int dir_virtual, unsigned int cr3, unsigned int dir_fisica,
	unsigned char present, unsigned char rw, unsigned char us) {
	unsigned int offset_directorio = dir_virtual;
	offset_directorio = offset_directorio  >> 22;
	unsigned int offset_tabla = dir_virtual;
	offset_tabla = (dir_virtual >> 12) & 0x3FF;
	int i;

	page_directory_entry * page_dir_base = (page_directory_entry *) cr3;
	page_directory_entry * page_dir = &page_dir_base[offset_directorio];
	page_table_entry * page_table;

	if (page_dir->p) {
		page_table = (page_table_entry *) (page_dir->base_12_31 << 12) + offset_tabla;
	} else {
		define_page_directory_entry(page_dir, present, rw, us, 
			(unsigned int) MEMORIA_RESTANTE);

		page_table = (page_table_entry *) MEMORIA_RESTANTE + offset_tabla;
		for (i = 0; i < 1024; i++) {
			null_pagetab_entry(&page_table[i]);
		}
		MEMORIA_RESTANTE += TAMANO_PAGINA;
	}

	define_page_table_entry(page_table, present, rw, us, dir_fisica);
	tlbflush();
}	

void mmu_unmapear_pagina(unsigned int dir_virtual, unsigned int cr3) {
	unsigned int offset_directorio = dir_virtual;
	unsigned int offset_tabla = dir_virtual;

	page_directory_entry * page_dir_base = (page_directory_entry *) cr3;
	page_directory_entry * page_dir = page_dir_base + (offset_directorio  >> 22);

	if (page_dir->p) {
		page_table_entry * page_table = (page_table_entry *) (page_dir->base_12_31 & 0x000FFFFF) + (offset_tabla >> 12);
		null_pagetab_entry(page_table);
	}
}

void null_pagetab_entry(page_table_entry * tablaAVaciar) {
	tablaAVaciar->p = 0;
	tablaAVaciar->rw = 0;
	tablaAVaciar->us = 0;
	tablaAVaciar->pwt = 0x00;
	tablaAVaciar->pcd = 0x00;
	tablaAVaciar->a = 0x00;
	tablaAVaciar->d = 0x00;
	tablaAVaciar->pat = 0x00;
	tablaAVaciar->g = 0x00;
	tablaAVaciar->available = 0x00;
	tablaAVaciar->base_12_31 = 0x00000;
}

void null_pagedir_entry(page_directory_entry * directorioAVaciar) {
	directorioAVaciar->p = 0;
	directorioAVaciar->rw = 0;
	directorioAVaciar->us = 0;
	directorioAVaciar->pwt = 0x00;
	directorioAVaciar->pcd = 0x00;
	directorioAVaciar->a = 0x00;
	directorioAVaciar->ignored = 0x00;
	directorioAVaciar->ps = 0x00;
	directorioAVaciar->g = 0x00;
	directorioAVaciar->available = 0x00;
	directorioAVaciar->base_12_31 = 0x00000;
}

void copiar_pagina(unsigned int origen, unsigned int destino) {
	int* pag_origen = (int*)(origen);
	int* pag_destino= (int*)(destino);
	int i;
	for (i = 0; i < 1024; i++) {
		pag_destino[i] = pag_origen[i];
	}
}

unsigned int dame_pagina_libre() {
	unsigned int pagina_libre = MEMORIA_RESTANTE;

	MEMORIA_RESTANTE += TAMANO_PAGINA;

	return pagina_libre;
}




unsigned char dame_pos_inicial_fila(int id) {
	unsigned char res;
	if(id == 1)   res = TANQUE1_FIL_INICIAL;
	if(id == 2)   res = TANQUE2_FIL_INICIAL;
	if(id == 3)   res = TANQUE3_FIL_INICIAL;
	if(id == 4)   res = TANQUE4_FIL_INICIAL;
	if(id == 5)   res = TANQUE5_FIL_INICIAL;
	if(id == 6)   res = TANQUE6_FIL_INICIAL;
	if(id == 7)   res = TANQUE7_FIL_INICIAL;
	if(id == 8)   res = TANQUE8_FIL_INICIAL;
	return res;
}

unsigned char dame_pos_inicial_col(int id) {
	unsigned char res;
	if(id == 1) res = TANQUE1_COL_INICIAL;
	if(id == 2) res = TANQUE2_COL_INICIAL;
	if(id == 3) res = TANQUE3_COL_INICIAL;
	if(id == 4) res = TANQUE4_COL_INICIAL;
	if(id == 5) res = TANQUE5_COL_INICIAL;
	if(id == 6) res = TANQUE6_COL_INICIAL;
	if(id == 7) res = TANQUE7_COL_INICIAL;
	if(id == 8) res = TANQUE8_COL_INICIAL;
	return res;
}

unsigned int dame_fisica(unsigned int i, unsigned int j) {
	unsigned int res = 0X00400000;
	res = res +((i*50 + j)*4096);
	return res;
}
