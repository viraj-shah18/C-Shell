#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int cmd_mkdir(char *argv[]){
    printf("Hello this new mkdir command\n");
    char *create_dir_names[32];
    
    
    int i=1;
    if (argv[1]==NULL){
        printf("Argument missing\n");
        exit(EXIT_SUCCESS);
    }
    else{
        while (argv[i]!=NULL){
            create_dir_names[i-1]=argv[i];
            i++;
        }
        create_dir_names[i-1]=NULL;
    }

    int idx=0;
    while (create_dir_names[idx]!=NULL){
        int rc=mkdir(create_dir_names[idx], 0777);
        if (rc<0){
            printf("Creating new directory failed\n");
        }
        idx++;
    }
    return 0;
}