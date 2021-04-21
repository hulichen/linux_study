#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

//argc 程序运行参数的个数
//argv 所有的运行参数的字符串的地址的保存位置
int main (int argc, char *argv[], char *env[])
{
    int i;
    for (i = 0; argv[i] != NULL; i++) {
        printf("argv[%d]=[%s]\n", i, argv[i]);
    }
    for (i = 0; env[i] != NULL; i++) {
        printf("env[%d]=[%s]\n", i, env[i]);
    }
    return 0;
}
