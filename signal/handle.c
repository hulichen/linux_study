#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
void  sigcb(int  num){
  printf("handler  signal:  %d \n",num);
}

int  main ()
{
  
  signal(40, sigcb);
  while(1){
    printf("sleep......\n");
    sleep(10);
  }


  return  0 ;
}
