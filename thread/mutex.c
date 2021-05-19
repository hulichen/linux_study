/*=========================================================== 
*   Copyright (C) . All rights reserved.")
*   文件名称： 
*   创 建 者：zhang
*   创建日期：
*   描    述： 黄牛抢票
*       火车站有100张票；有四个黄牛党抢票--有票则抢，没票退出
===========================================================*/
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int tickets = 100;
pthread_mutex_t mutex;

void *scalpers(void *arg)
{
    while(1) {
        pthread_mutex_lock(&mutex);
        if (tickets > 0) {
            usleep(1);
            printf("我抢到了一张票：%p-%d\n", 
                    pthread_self(), tickets);
            tickets--;
        }else {
            //加锁后在任意有可能退出线程之前都要解锁
            pthread_mutex_unlock(&mutex);
            pthread_exit(NULL);
        }
        pthread_mutex_unlock(&mutex);
        usleep(1);
    }
    return NULL;
}
int main (int argc, char *argv[])
{
    int ret;
    pthread_t tid[4];
    //pthread_mutex_init(互斥锁，属性)
    pthread_mutex_init(&mutex, NULL);
    for (int i = 0; i < 4; i++) {
        ret = pthread_create(&tid[i], NULL, scalpers, NULL);
        if (ret != 0) {
            printf("create thread error\n");
            return -1;
        }
    }
    for (int i = 0; i < 4; i++) {
        pthread_join(tid[i], NULL);
    }
    pthread_mutex_destroy(&mutex);
    return 0;
}
