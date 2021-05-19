#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
int func()
{
    char *ptr = "马上要下课了!\n";
    //char ptr[] = "马上要下课了!\n";
    pthread_exit(ptr);
    return  3;
}
void *thr_entry(void *arg)
{
    //pthread_self()--用于获取调用线程的线程tid
    pthread_detach(pthread_self());
    char *ptr = (char *)arg;
    while(1) {
        sleep(3);
        func();
        //char *ptr = "nihao";
        //return ptr;
        printf("我只是一个普通线程-%s\n", ptr);
        sleep(1);
    }
    return NULL;
}
int main (int argc, char *argv[])
{
    pthread_t tid;
    int ret;
    char *ptr = "今天的太阳出来了!\n";
    //pthread_create(获取id， 属性， 入口函数， 传入数据)
    ret = pthread_create(&tid, NULL, thr_entry, ptr);
    if (ret != 0) {
        printf("thread create failed!\n");
        return -1;
    }
    //pthread_detach(tid);
    void *retval;
    ret = pthread_join(tid, &retval);
    if (ret == EINVAL) {
        printf("这个线程已经被分离\n");
    }
    printf("retval:%s\n", (char*)retval);
    //sleep(3);
    //pthread_cancel(tid);
    printf("%ul---%p\n", tid, tid);
    while(1) {
        printf("我是主线程\n");
        sleep(1);
    }
    return 0;
}
