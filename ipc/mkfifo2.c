#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>


int main(){
  char * filename = "./mkfifo.txt";
  int ret = mkfifo(filename,0664);
  if(ret<0 && errno!=EEXIST){
    perror("mkfifo error ");
    return -1;
  }
  int fd  = open(filename,O_RDONLY);
  if(fd<0){
    perror("open error");
    return -1;
  }
  while(1){
    char buf[1024]={0};
    int retr = read(fd,buf,1023);
    if(retr <0){
      perror("retr error");
      return -1;
    }
    else if(retr ==0){
      printf("\nall write is closed\n");
      return -1;
    }
    printf("%s",buf);
  }
  close(fd);
  return 0;
}
