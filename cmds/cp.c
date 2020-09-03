#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

#ifndef PATH_MAX
#define PATH_MAX 1024
#endif

int cp_file(){
    // TODO: read file and write
    return 0;
}


int cmd_cp(char *argv[]){
    int idx=1;
    while(argv[idx]!=NULL){
        char *src_name;
        char src_path[PATH_MAX];
        char dest_path[PATH_MAX];
        
        int r_flag=0;
        if (strcmp("-r", argv[idx])==0){
            r_flag=1;
            idx++;
        }
        
        if (argv[idx]==NULL){
            printf("cp:missing arguments\n");
            exit(EXIT_FAILURE);
        }

        if (getcwd(src_path, PATH_MAX)==NULL){
            printf("cp:getcwd failed\n");
            exit(EXIT_FAILURE);
        }
        src_name=argv[idx];
        strncat(src_path, "/", 1);
        strncat(src_path, argv[idx], strlen(argv[idx]));
        printf("%s\n", src_path);
        
        idx++;

        if (argv[idx]==NULL){
            printf("cp:missing arguments\n");
            exit(EXIT_FAILURE);
        }

        if (getcwd(dest_path, PATH_MAX)==NULL){
            printf("cp:getcwd failed\n");
            exit(EXIT_FAILURE);
        }
        strncat(dest_path, "/", 1);
        strncat(dest_path, argv[idx], strlen(argv[idx]));
        printf("%s\n", dest_path);
        idx++;
    }    
    if (idx==1){
        printf("cp:missing arguments\n");
        exit(EXIT_FAILURE);
    }

    // cp -r t1 t2
    // struct stat file_info;
    // char path[PATH_MAX];

    // if (getcwd(path, PATH_MAX)==NULL){
    //     printf("path error\n");
    //     exit(EXIT_FAILURE);
    // }    
    return 0;
}