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
void print_error(int eflags, int cs, int eip, int error_code) {
	int aux = eflags;
	__asm__("xchg %bx,%bx");
	aux++;
	/*if (error == 0)
	{
		char* mensaje0 = "Divide Error Exception (#DE)";
		int len = 60;
		//imprimir_texto_mp(mensaje0,len,0xF, 0,0);
	}*/
	/*if (error == 1)
	{
		"Debug Exception (#DB)";
	}
	if (error == 2)
	{
		"NMI Interrupt"; //Esta no habria que hacerla en este momento
	}
	if (error == 3)
	{
		"Breakpoint Exception (#BP)";
	}
	if (error == 4)
	{
		"Overflow Exception (#OF)";		
	}
	if (error == 5)
	{
		"BOUND Range Exceeded Exception (#BR)";		
	}
	if (error == 6)
	{
		"Invalid Opcode Exception (#UD)";		
	}
	if (error == 7)
	{
		"Device Not Available Exception (#NM)";
	}
	if (error == 8)
	{
		"Double Fault Exception (#DF)";		
	}
	if (error == 9)
	{
		
	}
	if (error == 10)
	{
		"Invalid TSS Exception (#TS)";
	}
	if (error == 11)
	{
		"Segment Not Present (#NP)";
	}
	if (error == 12)
	{
		"Stack Fault Exception (#SS)";
	}
	if (error == 13)
	{
		"General Protection Exception (#GP)";
	}
	if (error == 14)
	{
		"Page-Fault Exception (#PF)";
	}
	if (error == 15)
	{
		
	}
	if (error == 16)
	{
		"x87 FPU Floating-Point Error (#MF)";
	}
	if (error == 17)
	{
		"Alignment Check Exception (#AC)";
	}
	if (error == 18)
	{
		"Machine-Check Exception (#MC)";
	}
	if (error == 19)
	{
		"SIMD Floating-Point Exception (#XM)";
	}
	if (error == 20)
	{
		"Virtualization Exception (#VE)";
	}if (error == 32)
	{
		
	}*/
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