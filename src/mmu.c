/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del manejador de memoria
*/

#include "mmu.h"

void mmu_inicializar() {
	int i, j;
	str_page_directory_entry pd[1024];

	str_page_table_entry pt1[1024];
	str_page_table_entry pt2[1024];
	str_page_table_entry pt3[1024];
	str_page_table_entry pt4[1024];

	for (i = 0; i < 4; i++) {
		pd[i] = (str_page_directory_entry) {
			(unsigned char)	0x01			//   p:1;
			(unsigned char)	0x01			//   rw:1;
			(unsigned char)	0x00			//   us:1;
			(unsigned char)	0x00			//   pwt:1;
			(unsigned char)	0x00			//   pcd:1;
			(unsigned char)	0x00			//   a:1;
			(unsigned char)	0x00			//   ignored:1;
			(unsigned char)	0x00			//   ps:1;
			(unsigned char)	0x00			//   g:1;
			(unsigned char)	0x00			//   available:3;
			(unsigned int)	i * 4096		//   base_12_31:20;
		}

		str_page_table_entry pt[1024];
		if (i != 3) {
			for (j = 0; j < 1024; j++) {
				pt[j] = (str_page_table_entry) {
					(unsigned char)	0x01			//   p:1;
					(unsigned char)	0x01			//   rw:1;
					(unsigned char)	0x00			//   us:1;
					(unsigned char)	0x00			//   pwt:1;
					(unsigned char)	0x00			//   pcd:1;
					(unsigned char)	0x00			//   a:1;
					(unsigned char)	0x00			//   d:1;
					(unsigned char)	0x00			//   pat:1;
					(unsigned char)	0x00			//   g:1;
					(unsigned char)	0x00			//   available:3;
					(unsigned int)	j * 4096		//   base_12_31:20;
				}
			}
		} else {

		}

	}

	for (i = 4; i < 1024; i++) {
		pd[i] = (str_page_directory_entry) {
			(unsigned char)	0x00			//   p:1;
			(unsigned char)	0x00			//   rw:1;
			(unsigned char)	0x00			//   us:1;
			(unsigned char)	0x00			//   pwt:1;
			(unsigned char)	0x00			//   pcd:1;
			(unsigned char)	0x00			//   a:1;
			(unsigned char)	0x00			//   ignored:1;
			(unsigned char)	0x00			//   ps:1;
			(unsigned char)	0x00			//   g:1;
			(unsigned char)	0x00			//   available:3;
			(unsigned int)	i * 4096		//   base_12_31:20;
		}
	}
/*
	0x00000000 a 0x00DC3FFF
	14434303 bytes = 3 m y 11288575 bytes



1 pt -> 4 m

14434303 bytes -> aprox 14 m -> 4 pt

1 mega -> 1048576 bytes
3 mega -> 3145728 bytes
*/
}







