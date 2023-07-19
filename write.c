#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>

void write_file(const char *path, const char *data, int size, int offset) {
    
    int fd;
    int bytesWritten;
    fd = open(path, O_WRONLY);
    if (fd == -1) {
        printf("Error! Cannot open file.\n");
        return;
    }

    if (lseek(fd, offset, SEEK_SET) == -1) {
        printf("Error! Cannot jump to the specified offset.\n");
        close(fd);
        return;
    }

    bytesWritten = write(fd, data, size);
    if (bytesWritten == -1) {
        printf("Error! Cannot write to file.\n");
        close(fd);
        return;
    }
    printf("Written only %d bytes from data : %s\n", bytesWritten, data);
    printf("Data Successfully written.\n");
    close(fd);
}