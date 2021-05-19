#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <utime.h>

int tickets=1000;
pthread_mutex_t mutex;

void* scalpers(void *arg ){
  while(1){
    pthread_mutex_lock(&mutex);
    if(tickets>0){
      usleep(5);
      tickets--;
      printf("抢到一张票%p，剩余总票数为：%d\n",pthread_self(),tickets);
      pthread_mutex_unlock(&mutex);
    }
    else{
      pthread_mutex_unlock(&mutex);
      printf("票已经无了!\n");
      pthread_exit(NULL);
    }
    usleep(10);
  }
  return NULL; 
}


int main()
{
  int ret ;
  pthread_t tid[4];
  pthread_mutex_init(&mutex,NULL);
  for(int i=0;i<4;i++){
    ret = pthread_create(&tid[i],NULL,scalpers,NULL);
    if(ret!=0){
      perror("pthread_creat error\n");
      return -1;
    }
  }

  for(int i=0;i<4;i++){
    pthread_join(tid[i],NULL);
  }

  pthread_mutex_destroy(&mutex);
  return 0;
}
