/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de las rutinas de atencion de interrupciones
*/

#include "defines.h"
#include "idt.h"
#include "isr.h"

#include "tss.h"

idt_entry idt[256] = { };

idt_descriptor IDT_DESC = {
    sizeof(idt) - 1,
    (unsigned int) &idt
};

/*
    La siguiente es una macro de EJEMPLO para ayudar a armar entradas de
    interrupciones. Para usar, descomentar y completar CORRECTAMENTE los
    atributos y el registro de segmento. Invocarla desde idt_inicializar() de
    la siguiene manera:

    void idt_inicializar() {
        IDT_ENTRY(0);
        ...
        IDT_ENTRY(19);

        ...
    }
*/


#define IDT_ENTRY(numero)                                                                                        \
    idt[numero].offset_0_15 = (unsigned short) ((unsigned int)(&_isr ## numero) & (unsigned int) 0xFFFF);        \
    idt[numero].segsel = (unsigned short) (GDT_IDX_CODE_0 * 8);                                                                  \
    idt[numero].attr = (unsigned short) 0x8E00;                                                                  \
    idt[numero].offset_16_31 = (unsigned short) ((unsigned int)(&_isr ## numero) >> 16 & (unsigned int) 0xFFFF);

// attr
//1 00 01110 000 00000
//1000 1110 0000 0000
//8E00

unsigned int idt_inicializar() {
    IDT_ENTRY(0);
    IDT_ENTRY(1);
    IDT_ENTRY(2);
    IDT_ENTRY(3);
    IDT_ENTRY(4);
    IDT_ENTRY(5);
    IDT_ENTRY(6);
    IDT_ENTRY(7);
    IDT_ENTRY(8);
    IDT_ENTRY(9);
    IDT_ENTRY(10);
    IDT_ENTRY(11);
    IDT_ENTRY(12);
    IDT_ENTRY(13);
    IDT_ENTRY(14);
    IDT_ENTRY(15);
    IDT_ENTRY(16);
    IDT_ENTRY(17);
    IDT_ENTRY(18);
    IDT_ENTRY(19);
    
    int i;
    for (i = 20; i < 256; ++i) //no se si es 20 o 21 por la q no se usa
    {
        idt[i].offset_0_15 = (unsigned short) ((unsigned int)(&invalida) & (unsigned int) 0xFFFF);
        idt[i].segsel = (unsigned short) (GDT_IDX_CODE_0 * 8);   //puse code 0 * 8 ya que estoy alineado y las interrupciones van a code
        idt[i].attr = (unsigned short) 0x8E00;
        idt[i].offset_16_31 = (unsigned short) ((unsigned int)(&invalida) >> 16 & (unsigned int) 0xFFFF);
        i++;
    } //supongo que de la 20 a la 256 va a la misma macro, salvo la de teclado
     //Interrupcion de reloj.
    idt[interrupcion_clock].offset_0_15 = (unsigned short) ((unsigned int)(&_isr32) & (unsigned int) 0xFFFF);
    idt[interrupcion_clock].segsel = (unsigned short) (GDT_IDX_CODE_0 * 8);    
    idt[interrupcion_clock].attr = (unsigned short) 0x8E00;
    idt[interrupcion_clock].offset_16_31 = (unsigned short) ((unsigned int)(&_isr32) >> 16 & (unsigned int) 0xFFFF);

    //Interrupcion de Teclado.
    idt[interrupcion_teclado].offset_0_15 = (unsigned short) ((unsigned int)(&int_teclado) & (unsigned int) 0xFFFF);
    idt[interrupcion_teclado].segsel = (unsigned short) (GDT_IDX_CODE_0 * 8);  
    idt[interrupcion_teclado].attr = (unsigned short) 0x8E00;
    idt[interrupcion_teclado].offset_16_31 = (unsigned short) ((unsigned int)(&int_teclado) >> 16 & (unsigned int) 0xFFFF);
//como son de tipo instruccion se matiene el 8E00

    idt[interrupcion_software].offset_0_15 = (unsigned short) ((unsigned int)(&int_task) & (unsigned int) 0xFFFF);
    idt[interrupcion_software].segsel = (unsigned short) (GDT_IDX_CODE_0 * 8);  
    idt[interrupcion_software].attr = (unsigned short) 0xEE00;
    idt[interrupcion_software].offset_16_31 = (unsigned short) ((unsigned int)(&int_task) >> 16 & (unsigned int) 0xFFFF);
    return (unsigned int)tss_tanques;
}
