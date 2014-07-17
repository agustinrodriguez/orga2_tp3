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
          syscall_mover(E);
          syscall_misil( 0, -1, 512, 512);
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
 while(1){
    syscall_minar(E);
  }
    while(1) { __asm __volatile("mov $7, %%eax":::"eax"); }
}
