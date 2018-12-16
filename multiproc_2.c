#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include "util.h"
#include <string.h>
#include <sys/shm.h>



int main( int argc, char *argv[])
{ 
  int k;
  int j;
  int i;
  int rep;
  int flag;

  struct sembuf up = { 0,1,0};
  struct sembuf down = { 0,-1,0};
  
  int semid = semget (IPC_PRIVATE,2,0600);
  semctl(semid, 0 , SETVAL , 1);

  rep = atoi(argv[1]);
  
 for (i=2;i<argc;i++)
    { 
       pid_t pid = fork();
       if (pid==0)
        { 
          semop(semid,&down,1);
          init();
          semop(semid,&up,1);
      
        for (j=0;j<rep;j++)
         { 
           semop(semid,&down,1);
	   display(argv[i]); 
           semop(semid,&up,1);
          }
        exit(0);   
  }      
 
   } 
 
for(k=2;k<argc;k++)
   { 
       wait(NULL);
   }   
     
  semctl(semid,0,IPC_RMID);
  
  return 0;
}
