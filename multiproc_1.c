#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
//#include "display.h"
//#include "util.h"
int main(int argc, char*argv[])
{
  int i;
  int rep;
  struct sembuf up = { 0,1,0};
  struct sembuf down = { 0,-1,0};

  int semid = semget (IPC_PRIVATE,1,0600);
  int flag;
  semop(semid,&up,1);


  rep = atoi(argv[1]);
  if (fork())
  {     
    for (i=0;i<rep;i++)
    {
      semop(semid,&down,1); 
      display("%s\n",*argv[i]);
      semop(semid,&up,1);
    }     
    wait(NULL);      
  }
  else
  {         
    exit(0);
}

  flag = semctl(semid,0,IPC_RMID);
  return 0;
}
