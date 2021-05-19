#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void sigcb(int signum){  
  printf("receive sig :%d\n",signum);
}
int main()
{
  signal(2,sigcb);
  signal(40,sigcb);  //自定义处理方式处理信号。
  
  sigset_t set ; 
  sigemptyset(&set);  //清空set集合
  sigaddset(&set,40);
  sigaddset(&set,2);//将2和号信号加入到set集合
  if(sigismember(&set,2)&&sigismember(&set,40)){
      printf("2 & 40 is exist\n");
  }
  sigprocmask(SIG_BLOCK,&set,NULL);//将set设置为阻塞集合
  printf("回车继续运行\n");
  getchar();   //getchar会阻塞当前进程。直到获取一个字符输入。
  sigprocmask(SIG_UNBLOCK,&set,NULL);//从阻塞集合中移除set集合中的信号。
  printf("unblock\n");
  while(1){
    sleep(3);
    printf("----\n");
  }
  return  0;
}
