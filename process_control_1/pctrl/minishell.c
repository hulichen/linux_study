#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/wait.h>
#include <fcntl.h>

int main (int argc, char *argv[])
{
    while(1) {
        char buf[1024] = {0};
        printf("[user@host path]$ ");
        fflush(stdout);
        fgets(buf, 1023, stdin);
        buf[strlen(buf) - 1] = '\0';
        
        char *str =buf;
        int retdirect_flag =0; // 1 qingkong  2 zhuijia  
        char *retdirect_file = NULL; 
        while(*str !='\0'){
          if (*str =='>'){
            retdirect_flag = 1;
            *str ='\0';
            str++;
            if(*str =='>'){
              retdirect_flag=2;
              *str ='\0';
              str++;
            }
          }
          while(*str != '\0'&& *str ==' ' ){
            str++;
          }
          retdirect_file=str;
          while(*str != '\0'&& *str != ' '){
            str++;
          }
          *str ='\0';
          
          str++;
        }
        printf("%d -%s -%s \n ",retdirect_flag,retdirect_file,buf);
        fflush(stdout);

        char *ptr = buf;
        char myargv[32][32]={{0}};
        int myargc = 0;
        while(*ptr != '\0') {
            if (!isspace(*ptr)) {
                int count = 0;
                while(*ptr != '\0' && !isspace(*ptr)) {
                    myargv[myargc][count] = *ptr;
                    count++;
                    ptr++;
                }
                myargc++;
            }
            ptr++;
        }

        char *arg[32] = {NULL};
        for (int i = 0; i < myargc; i++) {
            arg[i] = myargv[i];
        }
        arg[myargc] = NULL;
        pid_t pid = fork();
        if (pid < 0) {
            continue;
        }else if (pid == 0) {
          if(retdirect_flag==1){// >>
            int fd = open(retdirect_file,O_CREAT|O_TRUNC|O_WRONLY,0664);
            dup2(fd,1);
          }
          if(retdirect_flag==2){//追加>>
            
            int fd = open(retdirect_file,O_RDWR|O_APPEND|O_CREAT, 0664);
            dup2(fd,1);
          }
            execvp(arg[0], arg);
            exit(-1);
        }
        wait(NULL);
    }
    return 0;
}
