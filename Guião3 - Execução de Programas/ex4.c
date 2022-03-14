#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>


int mysystem(char* command){


    int i, ret, status;
    char* args[20];
    char* cpy = strdup(command);
    char* buffer;

    i=0;

    while((buffer = strsep(&cpy," ")) != NULL){
        args[i]=buffer;
        i++;
    }

    args[i]=NULL;

    pid_t pid;
    int res;

    if((pid=fork())==0) { //porque é que depois da linha 26 corre?
        //printf("\n\n[FILHO | Proc:%d] PID: %d\n", i, getpid()); 
        ret = execvp(args[0], args); 
        _exit(ret);
    }else{

        if (pid != -1){
            
            pid_t child= wait(&status);

            if(WIFEXITED(status)){
                res= WIFEXITED(status);
            }
            else{
                res=-1;
            }
        }
        else {
            res=-1;
        }
    }

    return res;
}

int main(int argc, char* const argv[]){

    printf("\n\n############# EX4 #############\n");
    
    char* command1 = "ls -l -a -h";
    char* command2 = "sleep 2";
    char* command3 = "ps";
    int ret;

    printf("Command1: %s\n", command1);
    ret = mysystem(command1);


    printf("\nCommand2: %s\n", command2);
    ret = mysystem(command2);

    printf("\nCommand3: %s\n", command3);
    ret = mysystem(command3);
}   