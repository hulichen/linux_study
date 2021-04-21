#include <unistd.h>
#include <string.h>
#include <stdio.h>

int  main ()
{
  int pipefd[2];
  pipe(pipefd);

  pid_t ret = fork();
  if(ret<0){
    perror("fork error");
    return -1;
  }
  else if (ret ==0)//子进程
  {
    close(pipefd[1]);//关闭写
    char buf[1024]={0};
    if(read(pipefd[0],buf,1023)!= -1)
      printf("%s\n",buf);
  }
  //父进程
  ////////////////
  close(pipefd[0]);//关闭读
  char *str= "i am father\n";  
    int retw=write(pipefd[1],str,strlen(str));
    if(retw==-1){
      perror("write error");
      return -1;
    }
  return 0;
}
