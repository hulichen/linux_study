#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

int main()
{
  char* filename = "./mkfifo.txt";
  int ret = mkfifo(filename,0664);
  if(ret<0 &&  errno!=EEXIST){
    perror("mkkfifo error");
    return -1;
  }
  int fd = open(filename,O_WRONLY);//只写方式打开文件。
  if(fd<0){
    perror("open error");
    return -1;
  }
  while(1){
    char buf[1024]={0};
    scanf("%s",buf);
    int retw = write(fd,buf ,strlen(buf));
    if(retw <0){
      perror("write error");
      return -1;
    }
  }
  close(fd);
  return  0;
}
