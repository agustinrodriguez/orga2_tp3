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
#include "game.h"

void mmu_inicializar();

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
} __attribute__((__packed__, aligned (8))) str_page_directory_entry;

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
} __attribute__((__packed__, aligned (8))) str_page_table_entry;


/* Page Directory */
extern str_page_directory_entry pd[];

#endif	/* !__MMU_H__ */




