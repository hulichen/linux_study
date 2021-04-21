#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int  main()
{
char *str = "abcdefghil";
int a =0 ;
while(1){
  char *p = malloc(sizeof(char)*1024);
  memcpy(p,str,10);
  a++;
  printf("%d G\n",a/1024);
}


  return 0 ;
}

