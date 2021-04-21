#include <stdio.h>
#include <string.h>
#include <unistd.h>
int main ()
{
  pid_t pid = fork();
  if(pid <0){
    perror("fork error");
    return -1;
  }

  perror("");
  return ;
}
