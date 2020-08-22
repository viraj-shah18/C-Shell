#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(){
    char *myargs[3];
    myargs[0]="ls";
    myargs[1]="-a";
    myargs[2]=NULL;
    execvp(myargs[0], myargs);
    return 0;
}