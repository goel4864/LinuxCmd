#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>

int create_named(const char* path,int mode){    
    int fd;
    umask(0);
    struct stat buff;
    fd=stat(path,&buff);
    if (fd != -1) 
    {
        printf("File already exists.\n");
        return -1;
    }
    close(fd); 
    int n = mknod(path, S_IFIFO | mode, 0);
    if(n==-1) 
    {
        printf("Error creating named pipe.\n");
        return -1;
    }
    return 0;
}
int writeToNamedPipe(const char *pipeName, const char *data) {
    
    struct stat buff;
    int n=stat(pipeName,&buff);
    if (n == -1) {
        printf("Cannot open named pipe for writing\n");
        return -1;
    }
    int pipe_fd = open(pipeName, O_WRONLY);
    if (write(pipe_fd, data, strlen(data)) == -1) {
        printf("Error! Cannot write to named pipe ");
        close(pipe_fd);
        return -1;
    }
    
    printf("Data %s in %s\n", data, pipeName);
    close(pipe_fd);
    return 0;
}

int readFromNamedPipe(const char *pipeName, int size) {
    struct stat buff;
    int n=stat(pipeName,&buff);
    if (n == -1) {
        printf("Cannot open named pipe for reading");
        return -1;
    }
    ssize_t bytesRead=0 ;
    ssize_t count=0;
//    char buffer[10];
//    int pipe_fd = open(pipeName, O_RDONLY);
//    while((bytesRead += read(pipe_fd, buffer,sizeof(buffer)))>0 && bytesRead<=size){
//         printf("Data : \t%s\n", buffer);
//    }

    char buffer[size];
    int pipe_fd = open(pipeName, O_RDONLY);
//    while((bytesRead += read(pipe_fd, buffer,size))>0 && bytesRead<=size){
//         printf("Data : \t%s\n", buffer);
//    }
    while ((count = read(pipe_fd, buffer, size))) {
    bytesRead += count;
    buffer[bytesRead] = '\0';
    printf("%s\n", buffer);
    if (bytesRead == size || count == -1)
      break;
  	}
    //Add the null pointer to end of buffer
    buffer[bytesRead] = '\0'; 
    close(pipe_fd);
    return 0;
}
