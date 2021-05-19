#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>    
#include <sys/shm.h>    
#include <sys/types.h>    
#include <stdlib.h>    
#include <string.h>
#define IPC_KEY 0x12345600    
#define PROJ_ID 0x12345678 


int main()
{

  int shmid= shmget(IPC_KEY,4096,IPC_CREAT|0664);
  if(shmid<0){
    perror("shmfet error");
    return -1;
  }

  void *shm_start =shmat(shmid,NULL,0);
  if(shm_start == (void*)-1){
    perror("shmaat error ");
    return -1;
  }
  while(1)
  {
    fgets((char*)shm_start,1024,stdin);
    sleep(1);
  }
  shmdt(shm_start);
  shmctl(shmid,IPC_RMID,NULL);
  return  0;
}
