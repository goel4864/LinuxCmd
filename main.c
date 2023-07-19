#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "create.c"
#include "read.c"
#include "write.c"
#include "display.c"
#include "named_pipe.c"
#include "unnamed_pipe.c"

int main(int argc, char *argv[]) {

    if (argc < 2) 
    {
        printf(" Error! Insufficient arguments \n");
        printf(" ./mainFile [command] \n");
        printf("\n F I L E   M E N U\t\t\t\t\tC O M M A N D \n To Create a file :\t\t\t\t\tcreate \n To Create a Named file :\t\t\t\tcreateNamed \n To Read from a file : \t\t\t\t\tread \n To Write to a file : \t\t\t\t\twrite\n To Display info about a file : \t\t\tdisplay \n To Copy a file to another file using unnamed pipe :\tcopyFileUsingUnnamedPipe\n To Read from a named Pipe : \t\t\t\treadFromNamedPipe \n To Write to named Pipe : \t\t\t\twriteToNamedPipe\n");
        return 1;
    }

    char *command = argv[1];

    if (strcmp(command, "create") == 0) {
        if (argc != 4) 
        {
             printf(" Error! Insufficient arguments Command : 'create'\n");
             printf("./mainFile create [filename] [permission] \n");
            return 1;
        }

        const char *path = argv[2];
        // Convert permission string to octal integer using strtol
        int mode = strtol(argv[3], NULL, 8);  
        //validate permissions
        // printf("Permissions: %d\n", mode);
        if (mode <= 0000) {
        printf("Error! Invalid permissions %s\n",argv[3]);
        return 1;
         }
        printf("Permissions: %04o\n", mode);
        int check=create_file(path, mode);
        if(check!=-1)
        {
            printf("File Created Successfully \n");
        }
        else
        {
            printf("Cannot Create a file \n");
            return 1;
        }
    } 
    else 
        if (strcmp(command, "read") == 0) 
        {
            if (argc != 5) {
            printf(" Error! Insufficient arguments Command : 'read'\n");
            printf(" ./mainFile read [filename] [offset] [size] \n");
            return 1;
        }

        const char *path = argv[2];
        int offset = atoi(argv[3]);
        int size = atoi(argv[4]);
        long total=read_file(path, size, offset);
        printf(" Bytes Successfully read : %ld\n",total);
    } 
    else 
        if (strcmp(command, "write") == 0) 
        {
            if (argc != 6) {
                printf(" Error! Insufficient arguments Command : 'write'\n");
                printf(" ./mainFile write [filename] [offset] [data] [size] \n ");
                return 1;
            }
            const char *path = argv[2];
            int offset = atoi(argv[3]);
            const char *data = argv[4];
            int size = atoi(argv[5]);

            write_file(path, data, size, offset);
        } 
        else 
            if (strcmp(command, "display") == 0) {
                if (argc != 3) 
                {
                    printf(" Error! Insufficient arguments Command : 'display'\n");
                    printf(" ./mainFile display [filename]\n ");
                    return 1;
                }
                const char *path = argv[2];
                display_file_info(path);
            }
            else 
                    if (strcmp(command, "copyFileUsingUnnamedPipe") == 0) {
                        if (argc < 4) 
                        {
                            printf(" Error! Insufficient arguments Command : 'copyFileUsingUnnamedPipe'\n");
                            printf(" ./mainFile copyFileUsingUnnamedPipe [sourceFilename] [destinationFilename]\n ");
                            return 1;
                        }
                        char *src = argv[2];
                        char *dest = argv[3];
                        int check=copyFileUsingUnnamedPipe(src, dest);
                        if(check!=-1)
                        {
                            printf("File Copied Successfully using unnamed pipe\n");
                        }
                        else
                        {
                            printf("File Copied Unsuccessfully using unnamed pipe\n");
                            return 1;
                        }
                    }
                    else
                    if(strcmp(command, "createNamed") == 0){
                       if (argc != 4) 
                        {
                             printf(" Error! Insufficient arguments Command : 'createNamed'\n");
                             printf("./mainFile createNamed [filename] [permission] \n");
                            return 1;
                        }
                        const char *path = argv[2];
                        // Convert permission string to octal integer using strtol
                        int mode = strtol(argv[3], NULL, 8);  
                        //validate permissions
                        if (mode <= 0000) 
                        {
	                        printf("Error! Invalid permissions %s\n",argv[3]);
	                        return 1;
	                    }
                        printf("Permissions: %04o\n", mode);
                        int check=create_named(path, mode);
                        if(check!=-1)
                        {
                            printf("NamedPipe Created Successfully \n");
                        }
                        else
                        {
                            printf("Cannot Create a Named Pipe \n");
                            return 1;
                        }

                    } 
                    else
                    	if(strcmp(command, "readFromNamedPipe") == 0)
                    	{
			                if (argc != 4) 
			                {
			                printf(" Error! Insufficient arguments Command : readFromNamedPipe\n");
                       		printf("./mainFile readFromNamedPipe [pipename] [size] \n");
                       		return 1;	
			            }
			            
			            const char *pipeName = argv[2];
			            int size = atoi(argv[3]);
			            
			     
			            if (readFromNamedPipe(pipeName, size) == -1) {
			                printf("Failed to read from named pipe.\n");
			                return 1;
			            }
			            
			            printf("Data Successfully readed \n");
                    	}
                    	else
                    		if(strcmp(command, "writeToNamedPipe") == 0)
                    		{
                    			if (argc != 4) {
                    				printf(" Error! Insufficient arguments Command : writeToNamedPipe\n");
                             		printf("./mainFile writeToNamedPipe [pipename] [data] \n");
                            		return 1;
					         
					            }
					            const char *pipeName = argv[2];
					            const char *data = argv[3];
					            
					            if (writeToNamedPipe(pipeName, data) == -1) {
					                printf("Failed to write to named pipe.\n");
					                return 1;
					            }
					            printf("Data Successfully written \n");
                    		}
		                    else 
		                     {
		                        printf("Invalid command: %s\n", command);
		                        printf("\n F I L E   M E N U\t\t\t\t\tC O M M A N D \n To Create a file :\t\t\t\t\tcreate \n To Create a Named file :\t\t\t\tcreateNamed \n To Read from a file : \t\t\t\t\tread \n To Write to a file : \t\t\t\t\twrite\n To Display info about a file : \t\t\tdisplay \n To Copy a file to another file using unnamed pipe :\tcopyFileUsingUnnamedPipe\n To Read from a named Pipe : \t\t\t\treadFromNamedPipe \n To Write to named Pipe : \t\t\t\twriteToNamedPipe\n");
		                        return 1;
		                    }
return 0;
}

