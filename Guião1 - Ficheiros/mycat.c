#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char const *argv[]){

    if (argc < 1) {
        printf("Not enough arguments");
        return 1;
    }

    int BUFFER_SIZE = 100;

    for (int i=0; i<argc; i++){
        int source = open(argv[i+1], O_RDONLY);

        char* buffer = malloc (sizeof(char)* BUFFER_SIZE);

        ssize_t scanner;

        while ((scanner = read(source,buffer, BUFFER_SIZE))>0){
            write(STDOUT_FILENO,buffer,scanner);
        }
    }
}