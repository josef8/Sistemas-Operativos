#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>  //dups dentro desta lib
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readln.c"

int main(int argc, char* argv[]){

    int fdp = open("/etc/passwd", O_RDONLY);
    int fdo = open("./saida/saida3.txt", O_CREAT | O_TRUNC | O_WRONLY, 0666);
    int fde = open("./erros/erros3.txt", O_CREAT | O_TRUNC | O_WRONLY, 0666);
    

    int fdin = dup(0); //guarda o stdin no fdin
    int fdout = dup(1); //guarda o stdout no fdout
    int fderror = dup(2);

    char* buf = malloc(sizeof(char)*1024);

    dup2(fdp,0); //associa ao fd0(strinput) o /etc/password
    dup2(fdo,1);
    dup2(fde,2);

    close(fdp);
    close(fdo);
    close(fde);

/*
    while(readln(0,buf, 1024) > 0){
        write(1,buf, strlen(buf));
        write(2,buf, strlen(buf));
    }
*/  
    int ret;

    ret = execl("/usr/bin/wc", "wc", "./saida/saida1.txt", NULL);
    


    dup2(fdin,0);
    dup2(fdout,1); 
    dup2(fderror,2);

    printf("Ret = %d", ret);
    close(fdin);
    close(fdout);
    close(fderror);

    return 0;

}
