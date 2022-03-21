#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>  //dups dentro de esta lib
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readln.c"


int main (int argc, char* argv[]){

    if (argc<3) return 1;

    char* args[argc-1];
    
    for(int i=0; i<argc-3; i++){
        args[i]=strdup(argv[i+3]);
    }
    args[argc-3] = NULL;

    if(!strcmp(argv[1],"-i")) {
        int fde =  open(argv[2], O_CREAT | O_RDONLY, 0666);
        if (dup2(fde,0)!= -1) execvp(args[0], args);
        else return 1;
    }
    else if(!strcmp(argv[1],"-o")){
        int fdo = open (argv[2], O_CREAT | O_APPEND | O_WRONLY, 0666);
         if (dup2(fdo,1)!= -1) execvp(args[0], args);
        else return 1;
    }
    else{
        printf("Input Errado");
    }


    return 0;

} 