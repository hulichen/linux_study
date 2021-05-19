#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <pthread.h>
#include <queue>
#include <cstdio>

#define MAX_THREAD  5    //线程数
#define  MAX_QUEUE 10   //任务队列容量
typedef void(*handler_t)(int);//定义一个函数类型指针*handler_t 返回值void 参数 int； 任务处理函数，需要任务入队时把处理方式传入
class ThreadTask{  //任务类，提供任务数据和处理任务函数
  public:
    ThreadTask()
    {}
    ThreadTask(int data,handler_t handler):_handler(handler),_data(data) 
    {}

    void Run(){
      _handler(_data);//线程池的线程获取到任务节点调用run就可以完成任务处理
    }
  private:
    int _data;//要处理的数据
    handler_t _handler; //数据的处理方法
};


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

    bool push(const ThreadTask& data){
      pthread_mutex_lock(&_mutex);
      if(_queue.size()==_capacity){
        pthread_cond_wait(&_cond_p,&_mutex);//队列已满则等待条件满足再放数据到队列
      }
      _queue.push(data);
      pthread_cond_signal(&_cond_c); // 唤醒
      pthread_mutex_unlock(&_mutex);
      return true;
    }

    bool pop(ThreadTask *data){
      pthread_mutex_lock(&_mutex);
      if(_queue.empty()){
        pthread_cond_wait(&_cond_c,&_mutex);//无数据则等待
      }
      *data = _queue.front();
      _queue.pop();
      pthread_cond_signal(&_cond_p);
      pthread_mutex_unlock(&_mutex);
      return true;
    }

  private:
    int _capacity;
    std::queue<ThreadTask> _queue;  
    pthread_cond_t _cond_p; //生产者条件变量
    pthread_cond_t _cond_c;  //消费者条件变量
    pthread_mutex_t _mutex;  //互斥锁
};

class ThreadPool{                                       
  public:                                               
    ThreadPool(int maxq=MAX_QUEUE,int maxt=MAX_THREAD)
      :max_thread(maxt),_queue(maxq)
    {
      int ret;
      pthread_t tid;
      for(int  i =0;i<maxq;++i){
        ret = pthread_create(&tid,NULL,thr_entry,this);
        //创建 把当前线程传入到线程入口函数,thr_entry中当前进程取任务处理
        if(ret!=0){
          exit(-1);
        }
        pthread_detach(tid);//等待
      }
    }                                                
    bool TaskPush(const ThreadTask & task){
      _queue.push(task);
      return true;
    }
  private:
    static void* thr_entry(void*arg){
      ThreadPool* p = (ThreadPool*)arg;
      while(1){
          ThreadTask task;
          p->_queue.pop(&task);//取出任务
          task.Run(); //调动任务的处理函数
      }
      return NULL;
    }
  private:
    int  max_thread;                                      
    BlockQueue _queue;    
};    


void testfunc(int data){ //自定义的任务处理函数，这里简单打印查看结果
 printf("%p--get data:%d, sleep %d sec\n", pthread_self(),
                 data, (data % 3) + 1);
     sleep((data % 3) + 1);
}
int  main ()
{  
  ThreadPool pool;
  for(int i=0;i<20;i++){
    ThreadTask task(i,testfunc);//创建个任务
    pool.TaskPush(task);
  }
  while(1){
    sleep(1);
  }
  return 0;
}
