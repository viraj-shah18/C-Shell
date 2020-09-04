#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

int create_daemon(char *curr_path){
    // step 1
    int fd;
    for(fd=sysconf(_SC_OPEN_MAX); fd>2; fd--){
        close(fd);
    }
    // printf("started with daemon\n");

    if (setsid()==-1){
        printf("daemon:error occured in setsid\n");
        exit(EXIT_FAILURE);
    }

    int rc2=fork();
    if (rc2<0){
        printf("daemon:fork failed\n");
        exit(EXIT_FAILURE);
    }
    else if(rc2>0){
        exit(EXIT_SUCCESS);
    }

    umask(0);
    if(chdir(curr_path)<0){
        printf("daemon:failed to change directories\n");
    }
    return 0;
}