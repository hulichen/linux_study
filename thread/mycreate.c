#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>



void func(){
  char* ptr="这是线程返回值\n";
  pthread_exit(ptr);
}

void* entry( void* arg ){
  pthread_detach(pthread_self());  //分离
  char *ptr=(char*)arg;
  printf("%s\n",ptr);
  while(1){
    printf("这是一个线程\n");
    sleep(5);
    func();
  }
  return NULL;
}


int  main (){
  pthread_t tid;
  int ret;
  char *ptr ="这是参数";
  pthread_create(&tid ,NULL,entry,ptr);
  void *retval ;
  ret= pthread_join(tid,&retval);
  if(ret == EINVAL){
    printf("该线程已经被分离\n");
    return -1;
  }
  printf("%s\n",(char*)retval);
  while(1){
    printf("这是主线程\n");
    sleep(1);
  }

  return 0;
}
