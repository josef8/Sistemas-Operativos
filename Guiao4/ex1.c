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

/*
Escreva um programa que redireccione o descritor associado ao seu standard input para o ficheiro
/etc/passwd, e o standard output e error respectivamente para saida.txt e erros.txt. Imedi-
atamente antes de o programa terminar, o mesmo deve imprimir no terminal a mensagem ”terminei”.
*/

int main (int argc, char* argv[]){

    int fdp = open("/etc/passwd", O_RDONLY);
    int fdo = open("./saida/saida1.txt", O_CREAT | O_TRUNC | O_WRONLY, 0666);
    int fde = open("./erros/erros1.txt", O_CREAT | O_TRUNC | O_WRONLY, 0666);
    

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

    while(readln(0,buf, 1024) > 0){
        write(1,buf, strlen(buf));
        write(2,buf, strlen(buf));
    }

    char line[] = "terminei\n";

    write(fdout, line, strlen(line));

    dup2(fdin,0);
    dup2(fdout,1); 
    dup2(fderror,2);

    close(fdin);
    close(fdout);
    close(fderror);

    return 0;

} 