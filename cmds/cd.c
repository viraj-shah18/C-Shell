#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int cmd_cd(char *argv[]){
    // checking for first argument
    if (argv[1]==NULL){
        printf("Path not specified\n");
    }
    else{
        int rc=chdir(argv[1]);
        if (rc<0){
            // if the path is not correct
            printf("Changing Directories failed - Directory not found\n");
        }
    }
    return 0;
}