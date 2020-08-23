#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int cmd_pwd(char *argv[]){
    char path[PATH_MAX];
    printf("This is custom pwd cmd\n");
    if (getcwd(path, PATH_MAX)==NULL){
        printf("error in cmd_pwd function\n");
    }else{
        printf("%s\n", path);
    }
    return 0;
}