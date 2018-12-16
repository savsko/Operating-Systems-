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

int rep;
pthread_mutex_t key;     

void* print(void* argv)
{ 
  char *string = (char*) argv;
  int j;  

 for (j = 0 ; j<rep;j++)
   {  
    pthread_mutex_lock(&key);  
    display(string);    
    pthread_mutex_unlock(&key);
   }
 //pthread_exit(NULL);

 }

int main(int argc, char *argv[])
{ 
  pthread_mutex_init(&key, NULL);   
  int i;
  pthread_t *t = malloc(sizeof(pthread_t) * (argc-2));  
  rep =atoi(argv[1]);
  for (i=0;i<(argc-2);i++)
  {
  pthread_create(&t[i],NULL,&print,(void*)argv[i+2]);

   
  } 
  for(i=0;i<(argc-2);i++)
  {  pthread_join(t[i],NULL);}
  pthread_mutex_destroy(&key); 
  return 0;
}
