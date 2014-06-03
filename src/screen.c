/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#include "screen.h"

void limpiar_pantalla() {
	int fila, col, modo = 0;
	unsigned char *mem_video = (unsigned char *) VIDEO_BASE;
	video_elem *elemento;

	modo = modo + C_FG_GREEN * 16; // asigno el color de fondo verde al modo

	for (fila = 0; fila < VIDEO_FILS; fila++) {
		for (col = 0; col < VIDEO_COLS; col++) {
			elemento = (video_elem *) mem_video;
			elemento->modo = (unsigned char) modo; //00100000b (verde);
			elemento->ascii = (unsigned char) 0; // caracter nulo
			mem_video = mem_video + 2;
		}
	}
}

void imprimir_texto(char * mensaje, int len) {
	int  i, modo = 0;
	unsigned char *mem_video = (unsigned char *) VIDEO_BASE;
	video_elem *elemento;

	modo = modo + C_FG_GREEN * 16;

	for (i = 0; i<len; i++) {
		elemento = (video_elem *) mem_video;
		elemento->modo = (unsigned char) modo; //00100000b (verde);
		elemento->ascii = mensaje[i];
		mem_video = mem_video + 2;
	}
}

/*se puede usar el imprimir texto de asm?*/
void print_error(int error_code) {
	//int aux = eflags;
	if (error_code == 0)
	{
		imprimir_texto("Divide Error Exception (#DE)",28);
	}
	if (error_code == 1)
	{
		imprimir_texto("Debug Exception (#DB)",21);
	}
	if (error_code == 2)
	{
		imprimir_texto("NMI Interrupt",13); //Esta no habria que hacerla en este momento
	}
	if (error_code == 3)
	{
		imprimir_texto("Breakpoint Exception (#BP)",26);
	}
	if (error_code == 4)
	{
		imprimir_texto("Overflow Exception (#OF)",25);		
	}
	if (error_code == 5)
	{
		imprimir_texto("BOUND Range Exceeded Exception (#BR)",37);		
	}
	if (error_code == 6)
	{
		imprimir_texto("Invalid Opcode Exception (#UD)",31);		
	}
	if (error_code == 7)
	{
		imprimir_texto("Device Not Available Exception (#NM)",36);
	}
	if (error_code == 8)
	{
		imprimir_texto("Double Fault Exception (#DF)",28);		
	}
	/*if (error_code == 9)
	{
		
	}*/
	if (error_code == 10)
	{
		imprimir_texto("Invalid TSS Exception (#TS)",27);
	}
	if (error_code == 11)
	{
		imprimir_texto("Segment Not Present (#NP)",25);
	}
	if (error_code == 12)
	{
		imprimir_texto("Stack Fault Exception (#SS)",27);
	}
	if (error_code == 13)
	{
		imprimir_texto("General Protection Exception (#GP)",34);
	}
	if (error_code == 14)
	{
		imprimir_texto("Page-Fault Exception (#PF)",26);
	}
	/*if (error_code == 15)
	{
		
	}*/
	if (error_code == 16)
	{
		imprimir_texto("x87 FPU Floating-Point Error (#MF)",34);
	}
	if (error_code == 17)
	{
		imprimir_texto("Alignment Check Exception (#AC)",31);
	}
	if (error_code == 18)
	{
		imprimir_texto("Machine-Check Exception (#MC)",30);
	}
	if (error_code == 19)
	{
		imprimir_texto("SIMD Floating-Point Exception (#XM)",35);
	}
	if (error_code == 20)
	{
		imprimir_texto("Virtualization Exception (#VE)",30);
	}
}
/*EXCEPTION AND INTERRUPT REFERENCE . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 6-19
Interrupt 0—Divide Error Exception (#DE) . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 6-20
Interrupt 1—Debug Exception (#DB) . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 6-21
Interrupt 2—NMI Interrupt . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 6-22
Interrupt 3—Breakpoint Exception (#BP). . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 6-23
Interrupt 4—Overflow Exception (#OF) . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 6-24
Interrupt 5—BOUND Range Exceeded Exception (#BR) . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 6-25
Interrupt 6—Invalid Opcode Exception (#UD) . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 6-26
Interrupt 7—Device Not Available Exception (#NM) . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 6-27
Interrupt 8—Double Fault Exception (#DF) . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 6-28
Interrupt 9—Coprocessor Segment Overrun. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 6-30
Interrupt 10—Invalid TSS Exception (#TS) . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 6-31
Interrupt 11—Segment Not Present (#NP) . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 6-34
Interrupt 12—Stack Fault Exception (#SS) . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 6-36
Interrupt 13—General Protection Exception (#GP). . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 6-37
Interrupt 14—Page-Fault Exception (#PF). . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 6-40
Interrupt 16—x87 FPU Floating-Point Error (#MF). . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 6-43
Interrupt 17—Alignment Check Exception (#AC). . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 6-45
Interrupt 18—Machine-Check Exception (#MC) . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 6-47
Interrupt 19—SIMD Floating-Point Exception (#XM) . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 6-48
Interrupt 20—Virtualization Exception (#VE) . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 6-50
Interrupts 32 to 255—User Defined Interrupts . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 6-51*/