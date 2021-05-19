#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <stdlib.h>
#define IPC_KEY 0X12345600
#define PROJ_ID 0x12345678
int  main()
{
// key_t key = ftok("./",PROJ_ID);
  int shmid = shmget(IPC_KEY,4096,IPC_CREAT|0664);
  if(shmid<0){
    perror("shmget error");
    return -1;
  }
  void*shm_start = shmat(shmid,NULL,0);
  sleep(2);
  if(shm_start==(void*)-1){
    perror("shmat error");
    return -1;
  }

  while(1)
  {
    sleep(1);
    for(int i=0;i<1024;i++){
      printf("%c",((char*)shm_start)[i]);
    }
    printf("\n");
  }

    shmdt(shm_start);
    shmctl(shmid,IPC_RMID,NULL);
    return 0;

}
