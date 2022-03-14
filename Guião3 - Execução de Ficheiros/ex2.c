#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


/* chamadas ao sistema: defs e decls essenciais */
// int execl(const char *path, const char *arg0, ..., NULL);
// int execlp(const char *file, const char *arg0, ..., NULL);
// int execv(const char *path, char *const argv[]);
// int execvp(const char *file, char *const argv[]);


int main(int argc, char* const argv[]){


    printf("\n\n############# EX2 #############\n");

    int ret, status;
    char* exec_args[] = {"/bin/ls","/bin/ls",NULL}; // o proc filho tem acesso a estas variáveis porque copia todo o conteudo
    pid_t pid;

    if((pid=fork())==0){

        printf("\n[FILHO %d] ", getpid());
        ret = execvp("ls", exec_args); // 0 se sucesso, -1 se não

        _exit(ret);
    }
    else{
        pid_t pid = wait(&status);

        if(WIFEXITED(status)) {
            printf("[PAI %d] processo filho %d terminou com sucesso | status = %d", getpid(), pid, WEXITSTATUS(status));
        }
        else {
            printf("[PAI %d] processo filho %d não foi encerrado corretamente | status = %d", getpid(), pid, WEXITSTATUS(status));
        }

    }

    return 0; 
}