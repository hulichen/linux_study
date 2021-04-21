#include <stdio.h>
#include <string.h>
#include <unistd.h>
int main ()
{
  int i;
  for (i=0 ;i<266;i++){
    printf("%s\n",strerror(i));
  }
  pid_t pid = fork();
  if(pid <0){
    perror("fork error");
    return -1;
  }
  char *p =NULL;
  memcpy(p,"aabbcc",3);
  perror("");
  return 0 ;
}
