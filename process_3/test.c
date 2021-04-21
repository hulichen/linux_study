#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
int main (int argc,char * argv[],char * env[]){
  printf("PATH = %s",getenv("PATH"));  
  printf("argc=%d\n",argc);
    for(int i =0;i<argc;i++){
      printf("%s\n",argv[i]);
    }
    for(int i =0;env[i]!=NULL;i++){
      printf("%s\n",env[i]);
    }
 // while(1){
 //   printf("hello  \n");
 //   sleep(1);
 // }
  return 0;
}
