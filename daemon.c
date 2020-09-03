#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

int create_daemon(){
    printf("started with daemon\n");

    int rc = fork();    
    if (rc < 0){
        printf("deamon:first fork failed\n");
        exit(EXIT_FAILURE);
    }

    if (rc > 0)
        exit(EXIT_SUCCESS);

    if (setsid()==-1){
        printf("daemon:error occured in setsid\n");
        exit(EXIT_FAILURE);
    }

    int rc2=fork();
    if (rc2<0){
        printf("daemon:second fork failed\n");
        exit(EXIT_FAILURE);
    }
    else if(rc2>0){
        exit(EXIT_SUCCESS);
    }

    printf("Parent id = %d\n\n", (int)getppid());
    umask(0);
    chdir("/");
    return 0;
}