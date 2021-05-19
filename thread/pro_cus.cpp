#include <iostream>
#include <queue>
#include <unistd.h>
#include <pthread.h>

#define MAX_QUEUE 5
class BlockQueue{
    private:
        int _capacity;//队列容量
        std::queue<int> _queue;
        pthread_mutex_t _mutex;
        pthread_cond_t _cond_pro;
        pthread_cond_t _cond_cus;
    public:
        BlockQueue(int que = MAX_QUEUE):_capacity(que){
            pthread_mutex_init(&_mutex, NULL);
            pthread_cond_init(&_cond_pro, NULL);
            pthread_cond_init(&_cond_cus, NULL);
        }  
        ~BlockQueue(){
            pthread_mutex_destroy(&_mutex);
            pthread_cond_destroy(&_cond_pro);
            pthread_cond_destroy(&_cond_cus);
        }
        //
        bool Push(const int &data) {
            pthread_mutex_lock(&_mutex);
            while(_queue.size() == _capacity) {//队列满了
                pthread_cond_wait(&_cond_pro, &_mutex);
            }
            _queue.push(data);
            pthread_cond_signal(&_cond_cus);
            pthread_mutex_unlock(&_mutex);
            return true;
        }
        bool Pop(int *data) {
            pthread_mutex_lock(&_mutex);
            while(_queue.empty() == true) {//队列为NULL
                pthread_cond_wait(&_cond_cus, &_mutex);
            }
            *data = _queue.front();
            _queue.pop();
            pthread_cond_signal(&_cond_pro);
            pthread_mutex_unlock(&_mutex);
        }
};

void *productor(void *arg)
{
    BlockQueue *q = (BlockQueue*)arg;
    int data = 0;
    while(1) {
        q->Push(data);
        printf("push data: %d\n", data++);
        sleep(1);
    }
    return NULL;
}
void *customer(void *arg)
{
    BlockQueue *q = (BlockQueue*)arg;
    while(1) {
        int data = 0;
        q->Pop(&data);
        printf("pop data: %d\n", data);
    }
    return NULL;
}
int main (int argc, char *argv[])
{
    BlockQueue q;
    int ret;
    pthread_t ptid[4], ctid[4];
    for (int i = 0; i < 4; i++) {
        ret = pthread_create(&ptid[i], NULL, productor, &q);
        if (ret != 0) {
            printf("thread create error\n");
            return -1;
        }
        ret = pthread_create(&ctid[i], NULL, customer, &q);
        if (ret != 0) {
            printf("thread create error\n");
            return -1;
        }
    }
    for (int i = 0; i < 4; i++) {
        pthread_join(ptid[i], NULL);
        pthread_join(ctid[i], NULL);
    }
    return 0;
}
