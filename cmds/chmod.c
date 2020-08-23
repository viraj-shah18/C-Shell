#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

int cmd_chmod(char *argv[]){
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
            printf("chmod failed. Please enter arguments carefully\n");
        }
        idx++;
    }
    return 0;
}