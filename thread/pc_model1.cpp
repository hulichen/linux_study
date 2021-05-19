#include <cstdio>
#include <unistd.h>
#include <vector>
#include <string>
#include <semaphore.h>
#include <pthread.h>

#define  MAX_QUEUE 5

class RingQueue
{
  public:
    RingQueue(int cap = MAX_QUEUE): 
      _capacity(cap) , _step_read(0),_step_write(0),_arry(cap)
  {

    sem_init(&_sem_data,0,0);
    sem_init(&_sem_idle,0, cap);
    sem_init(&_sem_lock,0 ,1);//用于实现互斥，初始信号量为1
  }
    ~RingQueue(){
      sem_destroy(&_sem_data);
      sem_destroy(&_sem_lock);
      sem_destroy(&_sem_idle);
    }

    bool Push(const int &data){
      sem_wait(&_sem_idle); //对空闲节点P操作，空闲节点-1， 小于0则阻塞
      sem_wait(&_sem_lock);//加锁
      //放数据
      _arry[_step_write] =data;
      _step_write=(_step_write+1)% _capacity;//写指针加一取模
      sem_post(&_sem_lock); //放完数据解锁，唤醒一个消费者
      sem_post(&_sem_data); //对数据节点V操作,数据节点+1
      return true;
    }
    bool Pop(int *buf){
      sem_wait(&_sem_data); //数据节点 -1    
      sem_wait(&_sem_lock); //加锁
      *buf= _arry[_step_read];//取数据
      _step_read =(_step_read+1)%_capacity;//读指针+1取模
      sem_post(&_sem_lock);//解锁
      sem_post(&_sem_idle);//空闲节点+1
      return true;
    }

  private:
    int _capacity;//容量
    int _step_read;//读指针
    int _step_write;//写指针
    std::vector<int> _arry;
    sem_t  _sem_data;//数据节点计数
    sem_t  _sem_idle;//空闲节点计数
    sem_t  _sem_lock;//用于实现互斥
};

void* productor(void *arg)
{
  RingQueue*q =(RingQueue*)arg;
  int data =0;
  while(1){
    q->Push(data);
    printf("push data : %d \n",data++);
    sleep(1);
  }
  return NULL;
}
void* customer(void *arg)
{
  RingQueue*q =(RingQueue*)arg;
  int data =0;
  while(1){
    q->Pop(&data);
    printf("pop data : %d \n", data);
    sleep(1);
  }
  return NULL;
}

int main ()
{
  RingQueue q ;
  int ret;
  pthread_t tid_p[4],tid_c[4];
  for(int i=0;i<4;++i){
    ret = pthread_create(&tid_p[i],NULL,productor,&q);
    if(ret !=0){
      perror("thread error\n");
    }
  }

  for(int i=0;i<4;++i){
    ret = pthread_create(&tid_c[i],NULL,customer,&q);
    if(ret !=0){
      perror("thread error\n");
    }
  }

  for(int i=0;i<4;++i){
    pthread_join(tid_c[i],NULL);
    pthread_join(tid_p[i],NULL);
  }

  return 0;
}
