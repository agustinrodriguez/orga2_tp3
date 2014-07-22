#include "colors.h"
#include "defines.h"
#include "game.h"
#include "syscall.h"

/*void task() {
   
  unsigned int i,j;
      syscall_minar(NO);
      syscall_minar(N);
      syscall_minar(SO);
      syscall_minar(S);
      syscall_minar(NE);
      syscall_minar(SE);
      for(j=0;j<24;j++){
        for(i=0;i<48;i++) {
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
  if(j>0 && j<23){
    syscall_misil( 1, 0, 512, 512);
    syscall_misil( 2, 0, 512, 512);
  }
  syscall_mover(N);
  if(j>0 && j<23){
    syscall_misil( 1, 0, 512, 512);
    syscall_misil( 2, 0, 512, 512);
    syscall_misil( 3, 0, 512, 512);
  }
  if(j == 0){
    syscall_misil( 1, 0, 512, 512);
  }
  syscall_mover(N);
}
for(i=0;i<47;i++) {
          syscall_misil( 1, 0, 512, 512);
          syscall_mover(E);
}
 while(1){
    syscall_minar(E);
  }
    while(1) { __asm __volatile("mov $7, %%eax":::"eax"); }
}
*/