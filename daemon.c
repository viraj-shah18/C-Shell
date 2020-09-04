#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

int create_daemon(){
    // used man 7 daemon to create this
    // step 1 - close all the file descriptors
    int fd;
    for(fd=sysconf(_SC_OPEN_MAX); fd>2; fd--){
        close(fd);
    }
    // setting child process as the leader of the session 
    if (setsid()==-1){
        printf("daemon:error occured in setsid\n");
        exit(EXIT_FAILURE);
    }
    // forking again so as to completly detach the process from the terminal
    int rc2=fork();
    if (rc2<0){
        printf("daemon:fork failed\n");
        exit(EXIT_FAILURE);
    }
    else if(rc2>0){
        exit(EXIT_SUCCESS);
    }

    // changing the file permissions
    umask(0);
    return 0;
}