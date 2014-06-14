/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de la tabla de descriptores globales
*/

#include "gdt.h"
#include "tss.h"
extern tss tss_inicial;

gdt_entry gdt[GDT_COUNT] = {
    /* Descriptor nulo*/
    /* Offset = 0x00 */
    [GDT_IDX_NULL_DESC] = (gdt_entry) {
        (unsigned short)    0x0000,         /* limit[0:15]  */
        (unsigned short)    0x0000,         /* base[0:15]   */
        (unsigned char)     0x00,           /* base[23:16]  */
        (unsigned char)     0x00,           /* type         */
        (unsigned char)     0x00,           /* s            */
        (unsigned char)     0x00,           /* dpl          */
        (unsigned char)     0x00,           /* p            */
        (unsigned char)     0x00,           /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     0x00,           /* db           */
        (unsigned char)     0x00,           /* g            */
        (unsigned char)     0x00,           /* base[31:24]  */
    },
    
    /* segmento de codigo */
    /* Offset = 0x09 */
    /* limit decimal 187648 */
    /* limit hexa 0x2DD00 */
    [GDT_IDX_CODE_0] = (gdt_entry) {
        (unsigned short)    0xDCFF,         /* limit[0:15]  */
        (unsigned short)    0x0000,         /* base[0:15]   */
        (unsigned char)     0x00,           /* base[23:16]  */
        (unsigned char)     0x0A,           /* type         */
        (unsigned char)     0x01,           /* s            */
        (unsigned char)     0x00,           /* dpl          */
        (unsigned char)     0x01,           /* p            */
        (unsigned char)     0x02,           /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     0x01,           /* db           */
        (unsigned char)     0x01,           /* g            */
        (unsigned char)     0x00,           /* base[31:24]  */
    },

    /* segmento de codigo */
    /* Offset = 0x0A */
    [GDT_IDX_CODE_3] = (gdt_entry) {
        (unsigned short)    0xDCFF,         /* limit[0:15]  */
        (unsigned short)    0x0000,         /* base[0:15]   */
        (unsigned char)     0x00,           /* base[23:16]  */
        (unsigned char)     0x0A,           /* type         */
        (unsigned char)     0x01,           /* s            */
        (unsigned char)     0x03,           /* dpl          */
        (unsigned char)     0x01,           /* p            */
        (unsigned char)     0x02,           /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     0x01,           /* db           */
        (unsigned char)     0x01,           /* g            */
        (unsigned char)     0x00,           /* base[31:24]  */
    },

    /* segmento de dato */
    /* Offset = 0x0B */
    [GDT_IDX_DATA_0] = (gdt_entry) {
        (unsigned short)    0xDCFF,         /* limit[0:15]  */
        (unsigned short)    0x0000,         /* base[0:15]   */
        (unsigned char)     0x00,           /* base[23:16]  */
        (unsigned char)     0x02,           /* type         */
        (unsigned char)     0x01,           /* s            */
        (unsigned char)     0x00,           /* dpl          */
        (unsigned char)     0x01,           /* p            */
        (unsigned char)     0x02,           /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     0x01,           /* db           */
        (unsigned char)     0x01,           /* g            */
        (unsigned char)     0x00,           /* base[31:24]  */
    },

    /* segmento de dato */
    /* Offset = 0x0C */
    [GDT_IDX_DATA_3] = (gdt_entry) {
        (unsigned short)    0xDCFF,         /* limit[0:15]  */
        (unsigned short)    0x0000,         /* base[0:15]   */
        (unsigned char)     0x00,           /* base[23:16]  */
        (unsigned char)     0x02,           /* type         */
        (unsigned char)     0x01,           /* s            */
        (unsigned char)     0x03,           /* dpl          */
        (unsigned char)     0x01,           /* p            */
        (unsigned char)     0x02,           /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     0x01,           /* db           */
        (unsigned char)     0x01,           /* g            */
        (unsigned char)     0x00,           /* base[31:24]  */
    },

    /* segmento de video */
    /* Offset = 0x0D */
    /* base 0xB8000 */
    /* limit 4000 (0xFA0) */

    [GDT_IDX_VIDEO] = (gdt_entry) {
        (unsigned short)    0x0F9F,         /* limit[0:15]  */
        (unsigned short)    0x8000,         /* base[0:15]   */
        (unsigned char)     0x0B,           /* base[23:16]  */
        (unsigned char)     0x02,           /* type         */
        (unsigned char)     0x01,           /* s            */
        (unsigned char)     0x00,           /* dpl          */
        (unsigned char)     0x01,           /* p            */
        (unsigned char)     0x00,           /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     0x01,           /* db           */
        (unsigned char)     0x01,           /* g            */
        (unsigned char)     0x00,           /* base[31:24]  */
    },

    /* tarea inicial */
    /* Offset = 0x0E */
    /* &tss_inicial 0x00000000 */
    [GDT_IDX_TAREA_INICIAL] = define_gdt_tss((unsigned int) &tss_inicial),

    /* tarea 1 */
    /* Offset = 0x0F */
    [GDT_IDX_TAREA_1] = define_gdt_tss((unsigned int)&tss_next_1),

    /* tarea 2 */
    /* Offset = 0x10 */
    [GDT_IDX_TAREA_2] = define_gdt_tss((unsigned int)&tss_next_2),
};

gdt_descriptor GDT_DESC = {
    sizeof(gdt) - 1,
    (unsigned int) &gdt
};

gdt_entry define_gdt_tss(unsigned int dir_tarea) {
    return (gdt_entry) {
        .limit_0_15     = 0x0067,
        .base_0_15      = dir_tarea & 0xFFFF,
        .base_23_16     = (dir_tarea >> 16) & 0xFF,
        .type           = 0x09,
        .s              = 0x00,
        .dpl            = 0x00,
        .p              = 0x01,
        .limit_16_19    = 0x00,
        .avl            = 0x00,
        .l              = 0x00,
        .db             = 0x01,
        .g              = 0x01,
        .base_31_24     = dir_tarea >> 24,
    };
}
