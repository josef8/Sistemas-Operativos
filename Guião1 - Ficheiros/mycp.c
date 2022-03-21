#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


// int open(const char *path, int flag, [,mode])
// ssize_t read (int fildes, void *buf, size_t nbyte)
// ssize_t write(int fildes, const void*buf, size_t nbyte)
// off_t lseek(int fd, off_t offset, int whence)
// in close (int fildes)

//argc guarda o nº de argumentos 
//argv guarda a linha de commando como um array de strings

int main(int argc, char const *argv[]){

    if (argc < 3) { 
        printf("Incorrect Number of Arguments");
        return 1;
    }

    int BUFFER_SIZE = 100;

    if (argc == 4) BUFFER_SIZE = atoi(argv[3]);

    clock_t start = clock();

    int source = open(argv[1], O_RDONLY);

    if(source == -1) {
        printf("mycp: impossível obter informação para '%s': Ficheiro ou pasta inexistente\n", argv[1]);
        exit(1); //EXIT_FAILURE
    }
    
    char* buffer = malloc(BUFFER_SIZE);

    int dest = open(argv[2],  O_CREAT | O_WRONLY, 0666); //0644 = -rw -r -r 

    ssize_t scanner; 

    while ((scanner = read(source,buffer,BUFFER_SIZE))>0){
        write(dest,buffer,scanner);
    }

    clock_t end = clock();

    float seconds = (float)(end - start) / CLOCKS_PER_SEC;

    printf("\nmycp: %lf seconds\n", seconds);

    close(source);
    close(dest);

    return 0;
}
