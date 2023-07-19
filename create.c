#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>

int create_file(const char *path, int mode) {
    int fd;
    umask(0);
    fd = open(path, O_RDONLY);
    if (fd != -1) 
    {
        printf("File already exists...\n");
        close(fd);
        return -1;
    }
    else 
    {
        fd = creat(path, mode);
        if (fd == -1) 
        {
            printf("Error! Cannot create a file.\n");
            return -1;
        } 
        close(fd);
    }
    return 0;
}
