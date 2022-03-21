#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

ssize_t readln(int fd, char* line, size_t size){

    ssize_t i=0;

    while (i<size-1){
        ssize_t scanner = read(fd, &line[i], 1);
        if (scanner<1) break;
        if(line[i++] == '\n') break;
    }

    line[i] = '\0';

    return i;
}

