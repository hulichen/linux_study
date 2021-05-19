#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <queue>
#include <stdio.h>

#define  MAX_QUEUE 10 


class BlockQueue{
  public:
    BlockQueue(int que_capacity=MAX_QUEUE):_capacity(que_capacity)
    {  
      pthread_mutex_init(&_mutex,NULL);
      pthread_cond_init(&_cond_p,NULL);
      pthread_cond_init(&_cond_c,NULL);
    }

    ~BlockQueue(){
      pthread_mutex_destroy(&_mutex);
      pthread_cond_destroy(&_cond_p);
      pthread_cond_destroy(&_cond_c);
    }

    bool push(const int& data){
      pthread_mutex_lock(&_mutex);
      if(_queue.size()==_capacity){
        pthread_cond_wait(&_cond_p,&_mutex);//队列已满则等待条件满足再放数据到队列
      }
      _queue.push(data);
      printf("productor %p push data: %d queue-size: %d \n",pthread_self(),data,_queue.size());
      pthread_cond_signal(&_cond_c); // 唤醒
      pthread_mutex_unlock(&_mutex);
      return true;
    }

    bool pop(int *data){
      pthread_mutex_lock(&_mutex);
      if(_queue.empty()){
        pthread_cond_wait(&_cond_c,&_mutex);//无数据则等待
      }
      *data = _queue.front();
      _queue.pop();
      printf("customer %p pop data: %d  queue-size: %d :\n",pthread_self(),*data,_queue.size());
      pthread_cond_signal(&_cond_p);
      pthread_mutex_unlock(&_mutex);
      return true;
    }

  private:
    int _capacity;
    std::queue<int> _queue;  
    pthread_cond_t _cond_p; //生产者条件变量
    pthread_cond_t _cond_c;  //消费者条件变量
    pthread_mutex_t _mutex;  //互斥锁
};



void* productor(void* arg){
 
  BlockQueue *q = (BlockQueue*)arg;
  int data=1;
  while(1){
    q->push(data++);
   usleep(1000000);
  }
  return NULL;
}

void* customer(void* arg){
  BlockQueue *q = (BlockQueue*)arg;
  while(1){
   int data=0;//获取pop的数据
    q->pop(&data);
    usleep(1000000);
  }
  return NULL;
}

int  main ()
{  
  BlockQueue q;
  int ret ;
  pthread_t ptid[4],ctid[4];
  for(int i=0;i<4;i++){ //这里创建了四个priductor线程
    ret=pthread_create(&ptid[i],NULL,productor,&q);
    if(ret!=0){
      perror("pthread_create error\n");
      return -1;
    }
  }

  for(int i=0;i<4;i++){//创建四个costomer线程
    ret=pthread_create(&ctid[i],NULL,customer,&q);
    if(ret!=0){
      perror("pthread_create error\n");
      return -1;
    }
  }

  for(int i=0;i<4;i++){
    pthread_join(ctid[i],NULL);
    pthread_join(ptid[i],NULL);
  }

  return 0;
}
