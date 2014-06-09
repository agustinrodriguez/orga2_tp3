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

DC3FFF



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

/* INICIO MAPA 0X400000 == 4194304
FIN MAPA 0XDC3FFF == 14434303

total =  10240000 bytes

9 megas y 0,765625
784 k = 196 paginas

*/
void mmu_inicializar_dir_tareas(){
	unsigned char rw;
	unsigned char us;
	unsigned char present;
	unsigned int cr3_para_dir;
	int i,j = 0;
	unsigned int MEMORIA_RESTANTE = MEMORIA_LIBRE; //no se si tengo q arrancar desde la memoria del mapa u otra
	unsigned int MEMORIA_PARA_COMBATE = LA_ARENA;
	unsigned int MEMORIA_VIRTUAL = 0x08000000;
	i = 0;
	rw = 1;
	us = 0;
	present = 1; //no se si va 1 o no
	//CON ESTE CICLO SUPUESTAMENTE ESTOY CREANDO DIRECTORIOS Y 4 PAGINAS identity POR CADA DIR + otra no presente q se mapeara a la arena
	while(i < CANT_TAREAS){
		page_directory_entry * pdir = (page_directory_entry *) MEMORIA_RESTANTE;
		
		cr3_para_dir = MEMORIA_RESTANTE; //ESTO ES ASI??

		MEMORIA_RESTANTE = MEMORIA_RESTANTE + TAMAÑO_PAGINA;
		page_table_entry * ptab = (page_table_entry *)MEMORIA_RESTANTE;
		MEMORIA_RESTANTE = MEMORIA_RESTANTE + TAMAÑO_PAGINA;
		page_table_entry * ptab2 = (page_table_entry *)MEMORIA_RESTANTE;
		MEMORIA_RESTANTE = MEMORIA_RESTANTE + TAMAÑO_PAGINA;
		page_table_entry * ptab3 = (page_table_entry *)MEMORIA_RESTANTE;
		MEMORIA_RESTANTE = MEMORIA_RESTANTE + TAMAÑO_PAGINA;
		page_table_entry * ptab4 = (page_table_entry *)MEMORIA_RESTANTE;
		MEMORIA_RESTANTE = MEMORIA_RESTANTE + TAMAÑO_PAGINA;
		page_table_entry * ptab5 = (page_table_entry *)MEMORIA_PARA_COMBATE; //ESTO NO SE SI ESTA BIEN
		
		MEMORIA_RESTANTE = MEMORIA_RESTANTE + TAMAÑO_PAGINA;
		MEMORIA_PARA_COMBATE = MEMORIA_PARA_COMBATE + TAMAÑO_PAGINA;
		
		define_page_directory_entry(&pdir[0],present,rw,us,&ptab); //primer directorio a pagina 0
		define_page_directory_entry(&pdir[1],present,rw,us,&ptab2); //primer directorio a pagina 0
		define_page_directory_entry(&pdir[2],present,rw,us,&ptab3); //primer directorio a pagina 0
		define_page_directory_entry(&pdir[3],present,rw,us,&ptab4); //primer directorio a pagina 0
		define_page_directory_entry(&pdir[4],present,rw,us,&ptab5); //primer directorio a pagina 0
		
		//lleno los 1024 sectores de la tabla, haciendo esto mis cuentas no dan
		j = 0;
		while(j< 1024){
			define_page_table_entry(&ptab,present,rw,us,j * 4096);
			define_page_table_entry(&ptab2,present,rw,us,(j *4096)+4096);
			define_page_table_entry(&ptab3,present,rw,us,(4096*2)+(j*4096));
			define_page_table_entry(&ptab4,present,rw,us,(4096*3)+(j*4096));
			j++

		}
		//o estoy haciendo mal las cuentas o no se hace asi, porq no em da para hacer todos asi
		us = 1;
		present = 0;
		//aca deberia ir un ciclo supongo hasta la cantidad de entradas presentes de cada pagina SUPONGO
			
		define_page_table_entry(&ptab5,present,rw,us,ACA NO SE QUE BASE PONERLE);
		mmu_mapear_pagina(MEMORIA_VIRTUAL,cr3_para_dir,MEMORIA_PARA_COMBATE)
		MEMORIA_VIRTUAL = MEMORIA_VIRTUAL + TAMAÑO_PAGINA;
		MEMORIA_RESTANTE = MEMORIA_RESTANTE + TAMAÑO_PAGINA;
		MEMORIA_PARA_COMBATE = MEMORIA_PARA_COMBATE + TAMAÑO_PAGINA;
		i++;
	//NO SE COMO IR JUNTANDO LAS PAGINAS SI TODAS VAN CON PRESENTES O COMO
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

