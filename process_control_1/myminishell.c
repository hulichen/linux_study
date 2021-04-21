#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <ctype.h>

int main(int argc,char *argv[] )
{
  while(1){

    char buf[1024]={0};
    printf("[user@host path]$");
    fflush(stdout);
    fgets(buf,1023,stdin);
    buf[strlen(buf)-1]='\0';
    char *str=NULL;
    str = buf;
    char myargv[32][32]={{0}};
    int myargc = 0;
    while(*str!='\0'){
      if(*str != ' '){
        int count = 0;
        while(*str != '\0' && *str != ' '){
          myargv[myargc][count++]=*str;
          str++;
        }
        myargc++;
      }
      str++;
    }    
    // for(int i = 0; i <myargc;i++){
    //   printf("myargv[%d]=[%s]\n",i,myargv[i]);
    // }

    char *arg[32]={NULL};
    for(int i = 0; i <myargc;i++){
      arg[i]=myargv[i];
    }
    arg[myargc]=NULL;
    pid_t  pid = fork();
    printf("%d\n",pid);
    if(pid<0){
      printf("<0------------\n");
      continue;
    }
    else if(pid == 0){//子进程进行进程替换
      execvp(arg[0],arg);
      printf("==0------------\n");
      exit(-1);
    }
    printf(">0------------\n");
    wait(NULL);

  }
  return 0;
}
