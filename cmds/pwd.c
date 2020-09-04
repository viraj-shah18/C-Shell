#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef PATH_MAX
#define PATH_MAX 1024
#endif

int cmd_pwd(char *argv[]){
    /*
    This is my implementation of pwd command
    prints working directory using the getcwd system call

    Usage example
    >> pwd
    */
    char path[PATH_MAX];
    // printf("This is custom pwd cmd\n");
    if (getcwd(path, PATH_MAX)==NULL){
        printf("error in cmd_pwd function\n");
        exit(EXIT_FAILURE);
    }
    printf("%s\n", path);
    return 0;
}