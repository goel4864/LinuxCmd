#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
#include <pwd.h>
#include <grp.h>

void display_file_info(const char *path) {
    
    struct stat fileStat;
    if (stat(path, &fileStat) == -1) 
    {
        printf("Error! Cannot get file information.\n");
        return;
    }
    printf("File Statistics :\n");
    printf("Owner : %s\n", getpwuid(fileStat.st_uid)->pw_name);
    printf("Owner Id: %u\n",  fileStat.st_uid);
    printf("Group: %s\n", getgrgid(fileStat.st_gid)->gr_name);
    printf("Group Id: %u\n", fileStat.st_gid);
    printf("File Permissions: %o\n", fileStat.st_mode & 0777);
    printf("Inode Number: %lu\n", fileStat.st_ino);
    printf("Link Count: %lu\n", fileStat.st_nlink);
    printf("Device Number: %lu\n", fileStat.st_dev);
    printf("Block Number: %lu\n", fileStat.st_blocks);
    printf("File Size: %ld bytes\n", fileStat.st_size);
    printf("Last Access Time: %s", ctime(&fileStat.st_atime));
    printf("Last Modification Time: %s", ctime(&fileStat.st_mtime));
    printf("Last Status Change Time: %s", ctime(&fileStat.st_ctime));

}
