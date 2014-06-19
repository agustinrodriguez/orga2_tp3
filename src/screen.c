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

	modo = modo + C_FG_BLACK * 16; // asigno el color de fondo verde al modo

	for (fila = 0; fila < VIDEO_FILS; fila++) {
		for (col = 0; col < VIDEO_COLS; col++) {
			elemento = (video_elem *) mem_video;
			elemento->modo = (unsigned char) modo; //00100000b (verde);
			elemento->ascii = (unsigned char) 0; // caracter nulo
			mem_video = mem_video + 2;
		}
	}
}

unsigned int pasaje_a_mapa(int direccion){
	int i = direccion - 0X00400000;
	i = i/4096;
	i = i*2;
	i = i + 0xb8000;
	return i;
}

void imprimir_desalojo(unsigned int error){
	int inicio = VIDEO_BASE + 6346;
	switch(error){
		case 1:
			imprimir_texto_para_tanques("Interrupcion Intel", 18 , inicio, C_FG_WHITE);
			break;
		case 2:
			imprimir_texto_para_tanques("Destruccion por Mina", 20 , inicio, C_FG_WHITE);
			break;
		case 3:
			imprimir_texto_para_tanques("Destruccion por Misil", 21 , inicio, C_FG_WHITE);
			break;
		case 4:
			imprimir_texto_para_tanques("Destruccion por Superposición", 29 , inicio, C_FG_WHITE);
			break;	
	}
}


void caracter_pintado(int tanque, int lugar) {
	int modo = 0;
	//int len = 1;
	//int i;
	unsigned char *mem_video = (unsigned char *) lugar;
	video_elem *elemento;

	modo = modo + C_FG_LIGHT_GREY * 16; // asigno el color de fondo verde al modo
	modo = modo + C_FG_WHITE;
	
			elemento = (video_elem *) mem_video;
			elemento->modo = (unsigned char) modo; //00100000b (verde);
			elemento->ascii = tanque;
	
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

void print_error(int error_code) {
	switch(error_code) {
		case 0:
			imprimir_texto("Divide Error Exception (#DE)", 28);
			break;
		case 1:
			imprimir_texto("Debug Exception (#DB)", 21);
			break;
		case 2:
			imprimir_texto("NMI Interrupt", 13);
			break;
		case 3:
			imprimir_texto("Breakpoint Exception (#BP)", 26);
			break;
		case 4:
			imprimir_texto("Overflow Exception (#OF)", 25);
			break;
		case 5:
			imprimir_texto("BOUND Range Exceeded Exception (#BR)", 37);
			break;
		case 6:
			imprimir_texto("Invalid Opcode Exception (#UD)", 31);
			break;
		case 7:
			imprimir_texto("Device Not Available Exception (#NM)", 36);
			break;
		case 8:
			imprimir_texto("Double Fault Exception (#DF)", 28);
			break;
		case 9:
			imprimir_texto("Coprocessor Segment Overrun (reserved)", 38);
			break;
		case 10:
			imprimir_texto("Invalid TSS Exception (#TS)", 27);
			break;
		case 11:
			imprimir_texto("Segment Not Present (#NP)", 25);
			break;
		case 12:
			imprimir_texto("Stack Fault Exception (#SS)", 27);
			break;
		case 13:
			imprimir_texto("General Protection Exception (#GP)", 34);
			break;
		case 14:
			imprimir_texto("Page-Fault Exception (#PF)", 26);
			break;
		case 15:
			imprimir_texto("Intel reserved. Do not use.", 27);
			break;
		case 16:
			imprimir_texto("x87 FPU Floating-Point Error (#MF)", 34);
			break;
		case 17:
			imprimir_texto("Alignment Check Exception (#AC)", 31);
			break;
		case 18:
			imprimir_texto("Machine-Check Exception (#MC)", 30);
			break;
		case 19:
			imprimir_texto("SIMD Floating-Point Exception (#XM)", 35);
			break;
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

void pantalla_juego() {
	int fila, col, modo = 0;
	unsigned char *mem_video = (unsigned char *) VIDEO_BASE;
	unsigned char *mem_video1 = (unsigned char *) VIDEO_BASE;
	video_elem *elemento;
//PRIMERO PINTO EL CAMPO DE JUEGO
	modo = modo + C_FG_GREEN * 16; // asigno el color de fondo verde al modo

	for (fila = 0; fila < 50; fila++) {
		for (col = 0; col < 50; col++) {
			elemento = (video_elem *) mem_video;
			elemento->modo = (unsigned char) modo; //00100000b (verde);
			elemento->ascii = (unsigned char) 0; // caracter nulo
			mem_video = mem_video + 2;
		}
		if (fila == 5){
			mem_video1 = mem_video + 4;
		}
		mem_video = mem_video + 60; //COMO MI PANTALLA LLEGA HASTA 80 Y YO VI 50 TENGO Q SUMARLE LO FALTANTE (30 * 2)
		
	}

//HAGO EL BLOQUE ROJO Y EL GRIS
//CORRO dos lugares mas 
	modo = 0;
	modo = modo + C_FG_LIGHT_GREY  * 16; // asigno el color de fondo gris al modo
	int modored = 0;
	modored = modored + C_FG_RED * 16;
	for (fila = 5; fila < 39; fila++) {
			for (col = 53; col < 80; col++) {
				if (fila == 5){
					elemento = (video_elem *) mem_video1;
					elemento->modo = (unsigned char) modored; //00100000b (rojo);
					elemento->ascii = (unsigned char) 0; // caracter nulo
					mem_video1 = mem_video1 + 2;
				}else{
					elemento = (video_elem *) mem_video1;
					elemento->modo = (unsigned char) modo; //00100000b (gris);
					elemento->ascii = (unsigned char) 0; // caracter nulo
					mem_video1 = mem_video1 + 2;
				}
			}
		//COMO TRABAJO DE BYTES "PARES" EL ULTIMO LO TENGO Q HACER AFUERA EN ESTE CASO PORQ RECORRI IMPAR
			if (fila == 5){
				elemento = (video_elem *) mem_video1;
				elemento->modo = (unsigned char) modored; //00100000b (rojo);
				elemento->ascii = (unsigned char) 0; // caracter nulo
				mem_video1 = mem_video1 + 106; //COMO MI PANTALLA LLEGA HASTA 80 Y YO QUIERO VER DESDE EL 53 TENGO Q SUMARLE LO FALTANTE (53 * 2)
			}else{				
				elemento = (video_elem *) mem_video1;
				elemento->modo = (unsigned char) modo; //00100000b (gris);
				elemento->ascii = (unsigned char) 0; // caracter nulo
				mem_video1 = mem_video1 + 106; //COMO MI PANTALLA LLEGA HASTA 80 Y YO QUIERO VER DESDE EL 53 TENGO Q SUMARLE LO FALTANTE (53 * 2)
			}
	}
// HAGO EL ULTIMO BLOQUE DE ROJO
	mem_video1 = mem_video1 + 160;
	modo = 0;
	modo = modo + C_FG_RED * 16; // asigno el color de fondo ROJO al modo

	for (fila = 39; fila < 42; fila++) {
		for (col = 53; col < 80; col++) {
			elemento = (video_elem *) mem_video1;
			elemento->modo = (unsigned char) modo; //00100000b (ROJO);
			elemento->ascii = (unsigned char) 0; // caracter nulo
			mem_video1 = mem_video1 + 2;
		}
		//como quedo recorriendo impar me queda el ultimo pixel sin pintar
		elemento = (video_elem *) mem_video1;
		elemento->modo = (unsigned char) modo; //00100000b (gris);
		elemento->ascii = (unsigned char) 0; // caracter nulo
		mem_video1 = mem_video1 + 106; //COMO MI PANTALLA LLEGA HASTA 80 Y YO QUIERO VOLVER A LA COLUMNA 53 TENGO Q SUMARLE LO FALTANTE 
	}

// HAGO EL ULTIMO BLOQUE DE GRIS
	mem_video = mem_video1;
	mem_video = mem_video + 480;
	modo = 0;
	modo = modo + C_FG_LIGHT_GREY * 16; // asigno el color de fondo ROJO al modo

	for (fila = 46; fila < 50; fila++) {
		for (col = 53; col < 71; col++) {
			elemento = (video_elem *) mem_video;
			elemento->modo = (unsigned char) modo; //00100000b (ROJO);
			elemento->ascii = (unsigned char) 0; // caracter nulo
			mem_video = mem_video + 2;
		}
		mem_video = mem_video + 124; //COMO MI PANTALLA LLEGA HASTA 80 Y YO VI 71 TENGO Q SUMARLE LO FALTANTE PARA IR A LA POSICION CORRECTA 
	}

}

void imprimir_nombre_grupo() {
	int  i, modo = 0;
	unsigned char *mem_video = (unsigned char *) VIDEO_BASE;
	mem_video = mem_video + (55*2);
	char * mensaje = "Colombia";
	int len = 8;
	video_elem *elemento;	
	modo = modo + C_FG_GREEN * 16;
	for (i = 0; i<len; i++) {
		elemento = (video_elem *) mem_video;
		elemento->modo = (unsigned char) modo; //00100000b (verde);
		elemento->ascii = mensaje[i];
		mem_video = mem_video + 2;
	}

}

/*void imprimir_caracter(unsigned char c, unsigned char forecolour, unsigned char backcolour, int x, int y)
{
	int modo = 0;
	unsigned char *mem_video = (unsigned char *) VIDEO_BASE;
	video_elem *elemento;

	modo = modo + forecolour * 16; // asigno el color de fondo verde al modo
	elemento = (video_elem *) mem_video;
	elemento->modo = (unsigned char) modo; //00100000b (verde);
	elemento->ascii = (unsigned char) c;
}

void imprimir_numero_teclado(unsigned char tecla) {
	if (tecla == 0x0B) {
		imprimir_caracter('0', C_FG_WHITE, C_FG_BLACK, 0, 0);
	} else {
		imprimir_caracter(tecla + (unsigned char) + 29, C_FG_WHITE, tecla - (unsigned char) 30, 0, 0);
	}
}*/


void print_tablaerror() {
	//char string[] = "??? ????????";
	int inicio = VIDEO_BASE + 746 + 480;
	char cadena[8];
	int inicio_y = VIDEO_BASE + 746 + 480;
	imprimir_texto_para_tanques("eax", 3 , inicio, C_FG_BLACK);
	inicio = inicio + 8;
	convertir_a_string(estado_error.eax, cadena);
	imprimir_texto_para_tanques(cadena, 8, inicio, C_FG_WHITE);
	inicio = inicio + 312;
	imprimir_texto_para_tanques("ebx", 3, inicio, C_FG_BLACK);
	inicio = inicio + 8;
	convertir_a_string(estado_error.ebx, cadena);
	imprimir_texto_para_tanques(cadena, 8, inicio, C_FG_WHITE);
	inicio = inicio + 312;
	imprimir_texto_para_tanques("ecx", 3, inicio, C_FG_BLACK);
	inicio = inicio + 8;
	convertir_a_string(estado_error.ecx, cadena);
	imprimir_texto_para_tanques(cadena, 8, inicio, C_FG_WHITE);
	inicio = inicio + 312;
	imprimir_texto_para_tanques("edx", 3, inicio, C_FG_BLACK);
	inicio = inicio + 8;
	convertir_a_string(estado_error.edx, cadena);
	imprimir_texto_para_tanques(cadena, 8, inicio, C_FG_WHITE);
	inicio = inicio + 312;
	imprimir_texto_para_tanques("esi", 3, inicio, C_FG_BLACK);
	inicio = inicio + 8;
	convertir_a_string(estado_error.esi, cadena);
	imprimir_texto_para_tanques(cadena, 8, inicio, C_FG_WHITE);
	inicio = inicio + 312;
	imprimir_texto_para_tanques("edi", 3, inicio, C_FG_BLACK);
	inicio = inicio + 8;
	convertir_a_string(estado_error.edi, cadena);
	imprimir_texto_para_tanques(cadena, 8, inicio, C_FG_WHITE);
	inicio = inicio + 312;
	imprimir_texto_para_tanques("ebp", 3, inicio, C_FG_BLACK);
	inicio = inicio + 8;
	convertir_a_string(estado_error.ebp, cadena);
	imprimir_texto_para_tanques(cadena, 8, inicio, C_FG_WHITE);
	inicio = inicio + 312;
	imprimir_texto_para_tanques("esp", 3, inicio, C_FG_BLACK);
	inicio = inicio + 8;
	convertir_a_string(estado_error.esp, cadena);
	imprimir_texto_para_tanques(cadena, 8, inicio, C_FG_WHITE);
	inicio = inicio + 312;
	imprimir_texto_para_tanques("eip", 3, inicio, C_FG_BLACK);
	inicio = inicio + 8;
	convertir_a_string(estado_error.eip, cadena);
	imprimir_texto_para_tanques(cadena, 8, inicio, C_FG_WHITE);
	inicio = inicio + 312;
	imprimir_texto_para_tanques("cs", 2, inicio, C_FG_BLACK);
	inicio = inicio + 8;
	convertir_a_string(estado_error.cs, cadena);
	imprimir_texto_para_tanques(cadena, 8, inicio, C_FG_WHITE);
	inicio = inicio + 312;
	imprimir_texto_para_tanques("ds", 2, inicio, C_FG_BLACK);
	inicio = inicio + 8;
	convertir_a_string(estado_error.ds, cadena);
	imprimir_texto_para_tanques(cadena, 8, inicio, C_FG_WHITE);
	inicio = inicio + 312;
	imprimir_texto_para_tanques("es", 2, inicio, C_FG_BLACK);
	inicio = inicio + 8;
	convertir_a_string(estado_error.es, cadena);
	imprimir_texto_para_tanques(cadena, 8, inicio, C_FG_WHITE);
	inicio = inicio + 312;
	imprimir_texto_para_tanques("fs", 2, inicio, C_FG_BLACK);
	inicio = inicio + 8;
	convertir_a_string(estado_error.fs, cadena);
	imprimir_texto_para_tanques(cadena, 8, inicio, C_FG_WHITE);
	inicio = inicio + 312;
	imprimir_texto_para_tanques("gs", 2, inicio, C_FG_BLACK);
	inicio = inicio + 8;
	convertir_a_string(estado_error.gs, cadena);
	imprimir_texto_para_tanques(cadena, 8, inicio, C_FG_WHITE);
	inicio = inicio + 312;
	imprimir_texto_para_tanques("ss", 2, inicio, C_FG_BLACK);
	inicio = inicio + 8;
	convertir_a_string(estado_error.ss, cadena);
	imprimir_texto_para_tanques(cadena, 8, inicio, C_FG_WHITE);
	inicio = inicio + 312;
	imprimir_texto_para_tanques("eflags", 8, inicio, C_FG_BLACK);
	inicio = inicio + 8;
	convertir_a_string(estado_error.eflags, cadena);
	imprimir_texto_para_tanques(cadena, 8, inicio, C_FG_WHITE);


	inicio_y = inicio_y + 28;
	imprimir_texto_para_tanques("cr0", 3, inicio_y, C_FG_BLACK);
	inicio_y = inicio_y + 8;
	convertir_a_string(estado_error.cr0, cadena);
	imprimir_texto_para_tanques(cadena, 8, inicio_y, C_FG_WHITE);
	inicio_y = inicio_y + 312;
	imprimir_texto_para_tanques("cr2", 3, inicio_y, C_FG_BLACK);
	inicio_y = inicio_y + 8;
	convertir_a_string(estado_error.cr2, cadena);
	imprimir_texto_para_tanques(cadena, 8, inicio_y, C_FG_WHITE);
	inicio_y = inicio_y + 312;
	imprimir_texto_para_tanques("cr3", 3, inicio_y, C_FG_BLACK);
	inicio_y = inicio_y + 8;
	convertir_a_string(estado_error.cr3, cadena);
	imprimir_texto_para_tanques(cadena, 8, inicio_y, C_FG_WHITE);
	
}


void imprimir_texto_para_tanques(char * mensaje, int len, int inicio, char color) {
	int  i, modo = 0;
	unsigned char *mem_video = (unsigned char *) inicio;
	video_elem *elemento;

	modo = modo + C_FG_LIGHT_GREY * 16;
	modo = modo + (int) color;

	for (i = 0; i<len; i++) {
		elemento = (video_elem *) mem_video;
		elemento->modo = (unsigned char) modo; //00100000b (verde);
		elemento->ascii = mensaje[i];
		mem_video = mem_video + 2;
	}
}

void convertir_a_string(unsigned int valor, char * cadena){
	unsigned int valor_original = valor;
	unsigned int numero = 0;
	int i = 0;
	int j = 7;

	while (i < 8) {
		valor = valor_original;
		numero = (valor >> (i * 4)) & 0x0000000F;

		if (numero < 10) {
			numero += 48; // de 0 a 9 sumo 48 para que corresponda con el ascii
		} else {
			numero += 55; // lo mismo pero de A a F;
		}

		cadena[j] = numero;
		i++;
		j--;
	}
}