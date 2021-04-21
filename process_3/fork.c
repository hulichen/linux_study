#include <stdio.h>
#include <unistd.h>

int main()
{
  int i = 10;
  pid_t ret = fork();
    if(ret<0){
      return 0;
    }
    else if(ret ==0){
      //child
      printf("child; i = %d\n",i);
      printf("child;%p\n",&i);
    }
    else{
      //father
      i+=10;
      printf("father; i = %d\n",i);
      printf("father;  %p\n",&i);
    }
  return 0;
}
