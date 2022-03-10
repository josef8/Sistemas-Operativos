#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/*
pid_t getpid(void); - get pid
pid_t getppid(void); - get pai - pid
pid_t fork(void); - cria o processo filho
void _exit(int status); - termina o processo e tem a opção de guardar um valor no status
pid_t wait(int *status); espera que o status receba um valor diferente,
pid_t waitpid(pid_t pid, int *status, int options); - espera que o um processo específico termine
int WIFEXITED(int status);  macro - retorna 1 se o filho terminou direito
int WEXITSTATUS(int status);  macro - retorna o número guardado no status
*/


int main(int argc, char* argv[]){

//1
/*  printf("PID: %d\n", getpid());
    printf("Pai pid: %d\n", getppid());
*/
//2
/*    pid_t pid;
    int i=0;

    if( (pid=fork())==0) { //processo-filho
        i++;
        printf("filho: %d\n", i);

        printf("Filho PID: %d\n", getpid());
        printf("Filho PAI-PID: %d\n", getppid());

    }
    else {  //processo-pai

        i--;
        printf("Pai: %d\n", i);
        printf("PAI Filho-PID: %d\n", pid);
        printf("PAI-PID: %d\n", getpid());
        printf("PAI PAI-PID: %d\n", getppid());
    }   
*/

//3 Lança processos de forma sequencial
/*    int i;
    int status;
    int nproc=10;
    pid_t pid;

    for(i=0; i<nproc; i++) {
        
        if ((pid=fork()) == 0){
            printf("[Proc:%d] PID: %d\n", i, getpid()); 
            _exit(i);
        }

        else {
            pid_t child = wait(&status);
            printf("[pai] process id %d exited, exit code: %d\n",child, WEXITSTATUS(status)) ;
        }
    }

//4 lança processos de forma concorrente

    int i;
    int status;
    int nproc=10;
    pid_t pid;

    for(i=0; i<nproc; i++) {
        
        if ((pid=fork()) == 0){
            printf("[Proc:%d] PID: %d\n", i, getpid()); 
            _exit(i);
        } 
    }
    
    for(i=0; i<nproc; i++) {
        pid_t child = wait(&status);

        if (WEXITSTATUS(status)){
           printf("[pai %d] process id %d exited, exit code: %d\n",getpid(), child, WEXITSTATUS(status));
        } 
        else {
            printf("[pai] process id %d exited. child not terminated\n", child)
        }
    }
    */


//5 procura o numero numa matriz com vários processos
/*    
    if(argc<2){
        printf("Usage: program <needle>\n");
        exit(1);
    }
    
    int needle = atoi(argv[1]);
    int nrows=10, ncol=10000;
    int rand_max=10000;
    int** matriz;;
    int status;

    pid_t pid;


    printf("\nGenerating number 0 to %d...", rand_max);
    matriz= (int**) malloc(sizeof(int*)*nrows);

    for (int i=0; i<nrows; i++){
        matriz[i] = (int*) malloc(sizeof(int)*ncol);
        for (int j=0; j<ncol; j++)
            matriz[i][j] = rand() % rand_max; 
    }

    for(int row = 0; row< nrows; row++) {

        if ((pid=fork()) == 0){

            for (int col=0; col<ncol; col++)
                if (matriz[row][col] == needle) _exit(row);

            _exit (-1);    
        }

    }


    for(int i=0; i<nrows; i++) {
        pid_t child = wait(&status);

        if (WEXITSTATUS(status) < 255){
           printf("\nNúmero encontrado [linha %d] ", WEXITSTATUS(status));
        } 
        else {
            printf("\nNa linha %d - Número NÃO ENCONTRADO", i);

        }
    }
*/
//6 imprimir por ordem crscente os numeros de linha onde existem ocorrencias do número
// utilizar a função pid_t waitpid(pid_t pid, int *wstatus, int options);
//

if(argc<2){
        printf("Usage: program <needle>\n");
        exit(1);
    }
    
    int needle = atoi(argv[1]);
    int nrows=10, ncol=10000;
    int rand_max=10000;
    int** matriz;;
    int status;

    int arraypids[nrows];

    pid_t pid;


    printf("\nGenerating number 0 to %d...", rand_max);
    matriz= (int**) malloc(sizeof(int*)*nrows);

    for (int i=0; i<nrows; i++){
        matriz[i] = (int*) malloc(sizeof(int)*ncol);
        for (int j=0; j<ncol; j++)
            matriz[i][j] = rand() % rand_max; 
    }

    for(int row = 0; row< nrows; row++) {

        if ((pid=fork()) == 0){

            for (int col=0; col<ncol; col++)
                if (matriz[row][col] == needle) _exit(row); //se encontrar retorna a line

            _exit (-1);    //não encontrou retorna -1
        }
        else {
            arraypids[row] = pid; //como é o processo-pai guarda na var pid o pid do filho;
        }

    }


    for(int i=0; i<nrows; i++) {
        pid_t child = waitpid(arraypids[i], &status, 0); // espera por um processo em especifico

        if(WIFEXITED(status)){
            if (WEXITSTATUS(status) < 255){
               printf("\nNúmero encontrado [linha %d] ", WEXITSTATUS(status));
            } 
            else {
                printf("\nNa linha %d - Número NÃO ENCONTRADO", i);
            }
        }
        else {
            printf("\n Deu merda mermão");
        }
    }


}
