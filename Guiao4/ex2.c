#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>  //dups dentro de esta lib
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readln.c"

/* chamadas ao sistema: defs e decls essenciais */
//int dup(int fd); // duplica fd só 
//int dup2(int fd1, int fd2); //duplica da fonte -> destino



int main (int argc, char* argv[]){

    int fdp = open("/etc/passwd", O_RDONLY);
    int fdo = open("./saida/saida2.txt", O_CREAT | O_TRUNC | O_WRONLY, 0666);
    int fde = open("./erros/erros2.txt", O_CREAT | O_TRUNC | O_WRONLY, 0666);
    

    int fdin = dup(0);
    int fdout = dup(1);
    int fderror = dup(2);

    char* buf = malloc(sizeof(char)*1024);

    dup2(fdp,0); //associa ao fd0(strinput) o /etc/password
    dup2(fdo,1);
    dup2(fde,2);

    close(fdp);
    close(fdo);
    close(fde);

    int status;
    pid_t pid;

    setbuf(stdout, NULL);

    if ((pid=fork()) == 0){
        
        char buf[100];
        sprintf(buf, "[Filho] %d\n", getpid());
        write(1,buf, strlen(buf));
        write(2,buf, strlen(buf));

        while(readln(0,buf, 1024) > 0){
            write(1,buf, strlen(buf));
            write(2,buf, strlen(buf));
        }
        _exit(1);
    }
    else {
        pid_t wait_pid = wait(&status);

        char buf[100];
        sprintf(buf, "[Pai] %d\n", getpid());
        write(1,buf, strlen(buf));
        write(2,buf, strlen(buf));


        if(WIFEXITED(status)){
            printf("[Pai] %d\n", getpid());
        } 

    }

    dup2(fdin,0);
    dup2(fdout,1); 
    dup2(fderror,2);

    close(fdin);
    close(fdout);
    close(fderror);

    return 0;

} 