#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int cmd_cd(char *argv[]){
    /*
    This is my implementation of cd command
    It validates the arguments and then uses relative path
    using chdir system call to change directories
    
    Usage example
    >>> cd t1
    >>> cd ..
    etc. 
    */

    // checking for first argument
    if (argv[1]==NULL){
        printf("Path not specified\n");
    }
    else{
        int rc=chdir(argv[1]);
        if (rc<0){
            // if the path is not correct
            printf("cd:changing directories failed-directory not found\n");
        }
    }
    return 0;
}