#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

int create_daemon(){
    printf("started with daemon\n");
    if (setsid()==-1){
        printf("daemon:error occured in setsid\n");
        exit(EXIT_FAILURE);
    }
    int rc=fork();
    if (rc<0){
        printf("daemon:fork failed\n");
        exit(EXIT_FAILURE);
    }
    else if(rc>0){
        // parent
        exit(EXIT_SUCCESS);
    }

    // child
    printf("Parent id = %d\n\n", (int)getppid());
    umask(0);
    chdir("/");
    return 0;
}