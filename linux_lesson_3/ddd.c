#include <stdio.h>

void  fun(){
  int  aa   =  10 ;
  int bb = 20 ;
  int cc =  aa+bb;
  printf("cc=%d \n",cc);
  int * p = NULL;
  * p  = 'a';
}
void fun1(){
  fun();
  printf("fun1\n");
}
int  main()
{
  int  a =10 ;
  int b = 20;
  int c =30;
  fun1();
  printf("c=%d \n ",a+b);
  return 0 ;
}
