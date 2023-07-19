#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>

long read_file(const char *path, int size, int offset) {
    
    int fd;
    char buff[size];
    ssize_t bytesRead;
    //It represents the no of bytes successfully read defined in unistd
    //If the value is non-negative, it represents the actual number of bytes read or written. 
    //If the value is negative, it typically indicates an error condition. 

    fd = open(path, O_RDONLY);
    if (fd == -1) {
        printf("Error! Cannot open file.\n");
        return -1;
    }

    if (lseek(fd, offset, SEEK_SET) == -1) {
        printf("Error! Cannot jump to the specified offset.\n");
        close(fd);
        return -1;
    }
    long totalBytes = 0;
    while((bytesRead = read(fd, buff, sizeof(buff)))>0 && totalBytes<size){
         printf("Data : \t%s\n", buff);
        totalBytes += bytesRead;
    }
    buff[bytesRead] = '\0';
    //adding null character to indicate the end of string
    close(fd);
    return totalBytes;

}
