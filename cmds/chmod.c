#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

int cmd_chmod(char *argv[]){
    /*
    This is my implementation of chmod command
    It validates the arguments and then convert string to octal number

    Usage example
    >>> chmod t1/11 0777
    >>> chmod t1/12 0444 test.py 0777
    */

    // checks for all arguments
    if (argv[1]==NULL){
        printf("Please enter all the arguments\n");
        exit(EXIT_FAILURE);
    }
    if (argv[2]==NULL){
        printf("Please enter all the arguments\n");
        exit(EXIT_FAILURE);
    }
    // converting string to base 8 as required by chmod() 
    long int mode = strtol(argv[1], 0, 8);
    
    // loop to handle multiple files 
    int idx=2;
    while(argv[idx]!=NULL){
        int rc=chmod(argv[idx], mode);
        if (rc<0){
            printf("chmod:failed arguments error\n");
            exit(EXIT_FAILURE);
        }
        idx++;
    }
    return 0;
}