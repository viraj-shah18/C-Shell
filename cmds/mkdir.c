#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int cmd_mkdir(char *argv[]){
    /*
    This is my implementation of mkdir command
    It validates the arguments and aggregates all argv
    Starts with one directory, check if file mode is valid 
    and prints all files in that dir 

    Usage example
    >> mkdir test1 test2 test3
    */

    // printf("Hello this new mkdir command\n");
    if (argv[1]==NULL){
        printf("mkdir:file name missing\n");
        exit(EXIT_FAILURE);
    }

    int idx=1;
    while (argv[idx]!=NULL){
        // used the default mode of 0777 to create new dir
        int rc=mkdir(argv[idx], 0777);
        if (rc<0){
            printf("mkdir:creating new directory failed\n");
        }
        idx++;
    }
    return 0;
}