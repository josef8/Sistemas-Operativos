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
    
    printf("\n\n#############EX1#############\n");

    int ret;
    char* exec_args[] = {"/bin/ls","/bin/ls","NULL"};
    
    //todas os formatos possívieis, cada um tem maior utilidade dependendo do contexto
    ret = execl("/bin/ls", "/bin/ls", NULL);
    //ret = execlp ("ls", "/bin/ls", NULL);
    //ret = execv(exec_args[0],exec_args);
    //ret = execvp("ls", exec_args);

    return 0; 
}