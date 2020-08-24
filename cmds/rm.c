#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>


int delete_files(char *file_path){
    int rc = unlink(file_path);
    if (rc<0){
        printf("rm: file deletion failed\n");
    }
    return 0;
}


int delete_dir(char *dir_path){
    DIR *open_dir;
    struct dirent *read_dir;
    if ((open_dir=opendir(dir_path))==NULL){
        printf("Error opening directory\n");
        exit(EXIT_FAILURE);
    }

    while ((read_dir=readdir(open_dir))!=NULL){
        struct stat file_info;
        char *dir_name=read_dir->d_name;
        char in_path[PATH_MAX]="";
        strncpy(in_path, dir_path, strlen(dir_path));
        strncat(in_path, "/",1);
        strncat(in_path, dir_name,strlen(dir_name));
        
        int rc=stat(in_path,&file_info);
        if (rc<0){
            printf("rm -r: stat failed\n");
            exit(EXIT_FAILURE);
        }

        if (strcmp(dir_name,".")==0 || strcmp(dir_name,"..")==0) {
            continue;
        }

        if (S_ISDIR(file_info.st_mode)){
            delete_dir(in_path);
        }
        else{
            delete_files(in_path);
        }
    }
    if (rmdir(dir_path)<0){
        printf("rm:unable to delete the directory\n");
        exit(EXIT_FAILURE);
    }
    return 0;
}

int cmd_rm(char *argv[]){
    /*
    One of the important point here is I am using only absolute paths
    */
    
    struct stat file_info;
    char path[PATH_MAX];

    if (getcwd(path, PATH_MAX)==NULL){
        printf("path error\n");
        exit(EXIT_FAILURE);
    }

    int idx=1;
    while(argv[idx]!=NULL){
        int is_dir=0;
        if (strcmp(argv[idx], "-r")==0){
            idx++;
            is_dir=1;
        }

        if (argv[idx]==NULL){
            printf("rm:Argument missing\n");
            exit(EXIT_FAILURE);
        }

        char *name = argv[idx];
        int rc=stat(name,&file_info);
        if (rc<0){
            printf("rm: stat failed\n");
            exit(EXIT_FAILURE);
        }

        if (S_ISDIR(file_info.st_mode) && is_dir){
            char test_path[PATH_MAX];
            strncpy(test_path, path, strlen(path)+1);
            strncat(test_path, "/", 1);
            strncat(test_path, name, strlen(name));
            delete_dir(test_path);
        }

        else if (!is_dir){
            delete_files(argv[idx]);
        }
        else{
            printf("rm:invalid arguments\n");
            exit(EXIT_FAILURE);
        }
        idx++;
    }
    return 0;
}