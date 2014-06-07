/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del manejador de memoria
*/

#include "mmu.h"

void mmu_inicializar() {
	mmu_inicializar_dir_kernel();
}

/*
INICIO AREA LIBRE 0x100000 == 1048576
FIN AREA LIBRE 0x3FFFFF == 4194303

TOTAL: 3145728 bytes
EN 4096 = 768 directorios o tablas?



*/
void mmu_inicializar_dir_kernel() {
	int i;
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

page_table_entry * get_descriptor(unsigned int virtual, unsigned int cr3){
	page_directory_entry * directorio = (page_directory_entry *) cr3;
	page_directory_entry * dir = (&directorio[virtual]);
	// CONSIGO LA TABLA	
	unsigned int posicion_dir = (dir->base_12_31 << 12);
	//FRUTA? no se si tengo q usar dir_virtual o cambiarle algo lo movi 12 por los define
	page_table_entry * tabla = (page_table_entry *) posicion_dir;
	return tabla;
}

void mmu_mapear_pagina(unsigned int virtual, unsigned int cr3, unsigned int fisica){
	page_table_entry * descriptor = get_descriptor(virtual, cr3); //con el cr3 tendriamos el puntero al dir?
	define_page_table_entry(descriptor,1,1,1,fisica);
}

void mmu_unmapear_pagina(unsigned int virtual, unsigned int cr3){
	page_table_entry * descriptor = get_descriptor(virtual, cr3); //con el cr3 tendriamos q tener la tabla a desmapear
	null_pagetab_entry(descriptor);
}

void null_pagetab_entry(page_table_entry * tablaAVaciar){
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

