#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>

int copyFileUsingUnnamedPipe(char *src, char *dest) {
    
    int pipefd[2];
    /*
    pipefd[0] -> Reader of a pipe
    pipefd[1] -> writer of a pipe
    */
    if (pipe(pipefd) == -1) 
    {
        printf("Error! Cannot create a pipe ");
        return -1;
    }
    // pid_t -> Process ID.
    pid_t pid = fork();

    if (pid == -1) 
    {
        printf("Error in fork()! Cannot create child process\n ");
        return -1;
    }

    // Child process
    //Reading->pipe and Writing->destination
    if (pid == 0) {
        close(pipefd[1]);  // Close the writer end of the pipe
        int fd_dest = open(dest, O_WRONLY);
        if (fd_dest == -1) 
        {
            printf("Error! Cannot open destination file\n");
            return -1;
        }

        char buff[1024];
        ssize_t bytesRead;

        while ((bytesRead = read(pipefd[0], buff, sizeof(buff))) > 0) {
            if (write(fd_dest, buff, bytesRead) == -1) 
            {
                printf("Error! Cannot write to destination file\n");
                close(fd_dest);
                close(pipefd[0]);
                return -1;
            }
        }
        close(fd_dest);
        close(pipefd[0]);
    } 
    else 
    {
        // Parent process
        // Reading ->src and Writing ->pipe
        close(pipefd[0]);  // Close the read end of the pipe
        int fd_src = open(src, O_RDONLY);
        if (fd_src == -1) 
        {
            printf("Error! Cannot open source file\n");
            return -1;
        }
        char buff[1024];
        ssize_t bytesRead;

        while ((bytesRead = read(fd_src, buff, sizeof(buff))) > 0) 
        {
            if ( write(pipefd[1], buff, bytesRead) == -1) 
            {
                printf("Error! Cannot write to pipe\n");
                close(fd_src);
                close(pipefd[1]);
                return -1;
            }
        }
        close(fd_src);
        close(pipefd[1]);
    }
    return 0;
}
