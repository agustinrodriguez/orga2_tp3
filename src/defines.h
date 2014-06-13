/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================

    Definiciones globales del sistema.
*/

#ifndef __DEFINES_H__
#define __DEFINES_H__

/* Bool */
/* -------------------------------------------------------------------------- */
#define TRUE                    0x00000001
#define FALSE                   0x00000000
#define ERROR                   1


/* Misc */
/* -------------------------------------------------------------------------- */
#define CANT_TANQUES            8
#define PAGE_SIZE               0x00001000
#define TASK_SIZE               2 * 4096
#define CAMPO_SIZE              50


/* Indices en la gdt */
/* -------------------------------------------------------------------------- */
#define GDT_IDX_NULL_DESC           0
#define GDT_IDX_CODE_0				9
#define GDT_IDX_CODE_3				10
#define GDT_IDX_DATA_0				11
#define GDT_IDX_DATA_3				12
#define GDT_IDX_VIDEO				13
#define GDT_IDX_TAREA_INICIAL		14
#define GDT_IDX_TAREA_1				15
#define GDT_IDX_TAREA_2				16


/* Offsets en la gdt */
/* -------------------------------------------------------------------------- */
#define GDT_OFF_NULL_DESC           (GDT_IDX_NULL_DESC      << 3)

/*OFFSET DE PAGINACION*/
#define MAINPAGEDIR             0x00027000
#define FIRSTPAGETABLE			0x00028000
#define SECONDPAGETABLE			0x00029000
#define TRHEEPAGETABLE			0x0002A000
#define FOURPAGETABLE			0x0002B000
#define CANT_TAREAS				8
#define TAMANO_PAGINA           0x00001000
#define SECTORFREEMEM 			0x00100000


/*INTERRUPCIONES*/
#define interrupcion_clock 32 	
#define interrupcion_teclado 33
#define interrupcion_software 52

/* Direcciones fisicas de codigos */
/* -------------------------------------------------------------------------- */
/* En estas direcciones estan los códigos de todas las tareas. De aqui se
 * copiaran al destino indicado por TASK_<i>_CODE_ADDR.
 */
#define TASK_1_CODE_ADDR    0x00010000
#define TASK_2_CODE_ADDR    0x00012000
#define TASK_3_CODE_ADDR    0x00014000
#define TASK_4_CODE_ADDR    0x00016000
#define TASK_5_CODE_ADDR    0x00018000
#define TASK_6_CODE_ADDR    0x0001A000
#define TASK_7_CODE_ADDR    0x0001C000
#define TASK_8_CODE_ADDR    0x0001E000

#endif  /* !__DEFINES_H__ */
