#include <stdio.h>                                                                                      
#include <stdlib.h>                                                                                     
#include <string.h>                                                                                     
#include <unistd.h>                                                                                     
#include <time.h>
#include <sys/types.h>                                                                                  
#include <sys/wait.h>                                                                                   

#define COMLEN 4096                                                                                     
#define COMARG_N 32                                                                                     
#define TRUE 1

int main(int argc, char *argv[]) 
{                                                                                                       
    char *token;                                                                                        
    char *args[COMARG_N];                                                                               
    char *buff;                                                                                         
    int i;                                                                                              
    pid_t pid;                                                                                          

    while(TRUE) {                                                                                       
        printf("$ ");                                                                            

        buff = (char*) malloc(sizeof(char) * COMLEN);                                                 
        fgets(buff, COMLEN, stdin);                                                                   

        if (buff[strlen(buff) - 1] == '\n')                                                           
            buff[strlen(buff) - 1] = '\0';                                                            

        i = 0;                                                                                        
        token = strtok (buff, " ");                                                                   

        while (token != NULL && i < COMARG_N - 1) {                                                   
            args[i] = token;                                                                          
            token = strtok (NULL, " ");                                                               
            i++;                                                                                      
        }                                                                                             

        args[i] = NULL;                                                                               

        pid = fork();                                                                                 
        if (pid == 0)                  {                                                               
            execvp(args[0], &args[0]); 
	exit(0);                        
if(strcmp(args[0], "exit") == 0) break;}                                       
        else                                                                                          
            waitpid(pid, &i, WUNTRACED | WCONTINUED);                                                 

        free(buff);                                                                                   
    }                                                                                                 

    return 0;                                                                                             
}  
