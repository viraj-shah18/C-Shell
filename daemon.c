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
        printf("daemon:fork failed\n");
        exit(EXIT_FAILURE);
    }
    else if(rc2>0){
        exit(EXIT_SUCCESS);
    }

    umask(0);
    chdir(curr_path);
    // stdin=fopen("/dev/null","r");
    // stdout=fopen("dev/null","w+");
    printf("Parent id = %d\n\n", (int)getppid());
    return 0;
}