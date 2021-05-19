#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <utime.h>


void* entry_A(void* arg){
  while(1){
    printf("我是线程A\n");
    sleep(1);
  }
  return NULL;
}
void* entry_B(void* arg){
  while(1){
    printf("我是线程B\n");
    sleep(1);
  }
  return NULL;
}

int main()
{
  pthread_t tid_A,tid_B;
  int ret;
  ret =pthread_create(&tid_A,NULL,entry_A,NULL);
  if(ret!=0){
    perror("pthread error \n");
  }

  pthread_create(&tid_B,NULL,entry_B,NULL);
  if(ret!=0){
    perror("pthread error \n");
  }
  
  pthread_join(tid_A,NULL);
  pthread_join(tid_B,NULL);
  return 0;
}
