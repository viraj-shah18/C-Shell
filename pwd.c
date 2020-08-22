#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void cmd_pwd(){
    char path[PATH_MAX];
    if (getcwd(path, PATH_MAX)==NULL){
        printf("error in cmd_pwd function\n");
    }else{
        printf("%s\n", path);
    }
}