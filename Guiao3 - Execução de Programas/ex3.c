#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* const argv[]){


    printf("\n\n############# EX3 #############\n");

    int i, status, ret;
    pid_t pid;

    for(i=1; i<argc; i++) {
        
        if ((pid=fork()) == 0){
            printf("\n[FILHO | Proc:%d] PID: %d\n", i, getpid()); 
            
            ret = execlp(argv[i], argv[i], NULL);

            _exit(ret);
        } 
    }
    
    for(i=1; i<argc; i++) {
        pid_t child = wait(&status);

        if (WIFEXITED(status)){
           printf("[PAI %d] Process id %d exited, exit code: %d\n",getpid(), child, WEXITSTATUS(status));
        } 
        else {
            printf("[PAI %d] Process id %d exited. Child not terminated successfuly\n", getpid() ,child);
        }
    }
}