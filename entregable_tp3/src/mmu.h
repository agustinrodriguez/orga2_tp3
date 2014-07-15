/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del manejador de memoria
*/

#ifndef __MMU_H__
#define __MMU_H__

#include "defines.h"
#include "i386.h"
#include "tss.h"

void mmu_inicializar();
void mmu_inicializar_dir_kernel();
unsigned int mmu_inicializar_dir_tarea(int num_tarea);
unsigned int get_cr3_task(unsigned int id);

typedef struct str_page_directory_entry {
    unsigned char   p:1;
    unsigned char   rw:1;
    unsigned char   us:1;
    unsigned char   pwt:1;
    unsigned char   pcd:1;
    unsigned char   a:1;
    unsigned char   ignored:1;
    unsigned char   ps:1;
    unsigned char   g:1;
    unsigned char   available:3;
    unsigned int   	base_12_31:20;
} __attribute__((__packed__, aligned (4))) page_directory_entry;

typedef struct str_page_table_entry {
    unsigned char   p:1;
    unsigned char   rw:1;
    unsigned char   us:1;
    unsigned char   pwt:1;
    unsigned char   pcd:1;
    unsigned char   a:1;
    unsigned char   d:1;
    unsigned char   pat:1;
    unsigned char   g:1;
    unsigned char   available:3;
    unsigned int   	base_12_31:20;
} __attribute__((__packed__, aligned (4))) page_table_entry;

void define_page_table_entry(page_table_entry * tabla, 
	unsigned char present, unsigned char rw, unsigned char us, unsigned int base);
void define_page_directory_entry(page_directory_entry * directorio, 
	unsigned char present, unsigned char rw, unsigned char us, unsigned int base);
void mmu_mapear_pagina(unsigned int dir_virtual, unsigned int cr3, unsigned int fisica, unsigned char present, unsigned char rw, unsigned char us);
void mmu_unmapear_pagina(unsigned int dir_virtual, unsigned int cr3);
void null_pagetab_entry(page_table_entry * tablaAVaciar);
void null_pagedir_entry(page_directory_entry * directorioAVaciar);
void copiar_pagina(unsigned int origen, unsigned int destino);
unsigned int dame_pagina_libre();
unsigned int dame_direccion_mapa(int num_tarea);
unsigned char dame_pos_inicial_col(int id);
unsigned char dame_pos_inicial_fila(int id);
unsigned int dame_fisica(unsigned int i, unsigned int j);
void copiar_pagina_size(unsigned int origen, unsigned int destino, unsigned int size);

unsigned int dame_fisica_de_virtual(unsigned int dir_virtual,unsigned int cr3);
/* Page Directory */
//extern page_directory_entry pd[];

#endif	/* !__MMU_H__ */




