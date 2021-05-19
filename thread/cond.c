#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

int desk = 0; //0-没有饭；1-有饭
pthread_cond_t cond;
pthread_mutex_t mutex;

void *customer(void *arg)
{
    while(1) {
        //加锁
        pthread_mutex_lock(&mutex);
        if (desk == 0) {
            //阻塞等待--解锁，休眠，被唤醒后加锁
            pthread_cond_wait(&cond, &mutex);
        }
        printf("面还可以~~\n");
        desk = 0;
        //唤醒厨师
        pthread_cond_signal(&cond);
        //解锁
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}
void *cook(void *arg)
{
    while(1) {
        //加锁
        pthread_mutex_lock(&mutex);
        if (desk == 1) {
            //阻塞
            pthread_cond_wait(&cond, &mutex);
        }
        printf("你的饭好了!\n");
        desk = 1;
        //唤醒顾客
        pthread_cond_signal(&cond);
        //解锁
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}
int main (int argc, char *argv[])
{
    pthread_t ztid, ltid;   
    int ret;
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);
    for(int i = 0; i < 4; i++){
        ret = pthread_create(&ztid, NULL, customer, NULL);
        if (ret != 0) {
            printf("thread create error\n");
            return -1;
        }
        ret = pthread_create(&ltid, NULL, cook, NULL);
        if (ret != 0) {
            printf("thread create error\n");
            return -1;
        }
    }
    pthread_join(ztid, NULL);
    pthread_join(ltid, NULL);
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    return 0;
}
