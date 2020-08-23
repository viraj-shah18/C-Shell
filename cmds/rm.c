#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>



int delete_files(char full_path[]){
    int rc = unlink(full_path);
    if (rc<0){
        printf("rm: file deletion failed");
    }
    return 0;
}

int delete_dir(char full_path[],char dir_name[]){
    // TODO
    char in_path[PATH_MAX];
    strncpy(in_path, full_path, strlen(full_path));
    strncat(in_path, "/", 1);
    strncat(in_path, dir_name, strlen(dir_name));
    return 0;
}

int cmd_rm(char *argv[]){
    if (argv[1]==NULL){
        printf("rm:Argument missing\n");
        exit(EXIT_FAILURE);
    }
    
    int idx=1;
    struct stat file_info;
    char path[PATH_MAX];
     if (getcwd(path, PATH_MAX)==NULL){
        printf("path error\n");
        exit(EXIT_FAILURE);
    }
    while(argv[idx]!=NULL){
        int rc=stat(argv[idx],&file_info);
        if (rc<0){
            printf("rm: stat failed\n");
            exit(EXIT_FAILURE);
        }

        // TODO
        if (S_ISDIR(file_info.st_mode)){
            delete_dir();
        }

        // TODO
        else{
            delete_files();
        }

    }
    return 0;
}