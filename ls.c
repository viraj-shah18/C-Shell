#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>

#define SHELL_NAME "fish"

// stat
// isdir
// print

void ps(char* argv[]){
    int rc=fork();
    if (rc<0){
        printf("Command ps cannot be executed");
        return;
    }else if (rc==0)
    {
        // argv will be of form ["ps", "-p", "pid"]
        execl("/usr/bin/ps",argv);
    }else
    {
        int wc = wait(NULL);
        printf("ps ran successfully");
    }
}


void ls_print(int argc, char *argv[]){
    printf("In ls_print");
}

void read_dir(int argc, char *argv[]){
    printf("TODO");
}

int main(){
    // char *name[]=SHELL_NAME;
    printf("%s>", SHELL_NAME);
    return 0;
}