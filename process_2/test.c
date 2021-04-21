#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main()
{
  pid_t ret = fork();
  if(ret<0){
    printf("ret:%d\n",ret);
    return -1;
  }
  else if(ret ==0){
    //child
    while(1){
      sleep(1);
      printf("子进程：I :%d\n",getpid());
      printf("father :%d\n",getppid());
    }
  }
  else{
    //father
    printf("父进程：I :%d\n",getpid());
    printf("father :%d\n",getppid());
    sleep(30);
  }
  return 0;

}
