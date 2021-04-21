#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
    //extern char **environ;
    printf("XXXXX-----XXXXX\n");
    //execl("/usr/bin/ls","ls","-a","-l",NULL);///usr/bin/ls为ls程序路径
    
   // execle("ls","ls","-a","-l",NULL)//可以不用给程序的路径
   // printf("DDDDD----DDDDD\n");
    
   
    char *env[] = {"MYVAL=1000", NULL};
  //execlp("./arg", "arg", "-a", "-l", NULL);
   // execle("./arg", "arg", "-a", "-l", NULL, env);
  
  

    char *arg[] = {"./arg", "-a", "-l", NULL};
    execve("./arg", arg, env);
   // perror("execve error");
   // printf("leihoua~~~\n");
    printf("DDDDD----DDDDD\n");
    return 0;
}
