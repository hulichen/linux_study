#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork error");//程序的一种失败错误处理
        return -1;
    }else if (pid == 0) {
        sleep(5);
        exit(99);//退出子进程
    }
    int ret, status;
    ret = wait(&status);
    while((ret = waitpid(-1, &status, WNOHANG)) == 0) {
        printf("没有子进程退出，打一把麻将\n");
        sleep(1);
    }
    
    if (ret > 0) {
        if (WIFEXITED(status)) {
            printf("%d\n", WEXITSTATUS(status));
        } else {
            printf("进程异常退出\n");
        }
    }
    while(1) {
        printf("------------\n");
        sleep(1);
    }
    return 0;
}
