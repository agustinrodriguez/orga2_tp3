/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
*/

#include "colors.h"
#include "defines.h"
#include "game.h"
#include "syscall.h"

/*void task() {
    
  unsigned int i,j;
  direccion dir[4] = { N, E, S, O };
  int d = 0;
  int counter = 3;
  for(i=0;i<100;i++) {
      for(j=0;j<counter;j++)
         syscall_mover(dir[d]);
      counter = counter + 2;
      d = (d + 1) % 4;   
  }
  while(1) { __asm __volatile("mov $7, %%eax":::"eax"); }
}*/
void pisar(unsigned int m);
void task() {
    /* Tarea 3 */
  unsigned int i,j;
      syscall_minar(NO);
      syscall_minar(N);
      syscall_minar(SO);
      syscall_minar(S);
      syscall_minar(NE);
      syscall_minar(SE);
      //unsigned char aa[512];
      for(j=0;j<24;j++){
        for(i=0;i<47;i++) {
          syscall_misil( 1, 0, 512, 512);
          unsigned int mapo = syscall_mover(E);
          syscall_misil( 0, -1, 512, 512);
          pisar(mapo-0x1000+1);
          if (j == 0){
            syscall_minar(S);
          }
          if (i < 46){
            syscall_minar(N);      
          }
        }
  syscall_mover(N);
  syscall_mover(N);
}
    while(1) { __asm __volatile("mov $7, %%eax":::"eax"); }
}

void pisar(unsigned int m) {
  unsigned int i;
  char* p = (char*)m;
  for(i=0;i<PAGE_SIZE;i++) {
    p[i]=0xcd;
  }
}