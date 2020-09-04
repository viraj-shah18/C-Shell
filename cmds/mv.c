#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>

char *get_fname(char *src_path);

int cmd_mv(char *argv[]){
    int idx=1;
    while (argv[idx]!=NULL){
        char src_path[PATH_MAX];
        char dest_path[PATH_MAX];

        char src_name[strlen(argv[idx])];

        if (getcwd(src_path, PATH_MAX)==NULL){
            printf("mv:getcwd failed\n");
            exit(EXIT_FAILURE);
        }
        strncat(src_path, "/", 1);
        strncat(src_path, argv[idx], strlen(argv[idx]));

        char src_path_copy[PATH_MAX];
        strncpy(src_path_copy, src_path, strlen(src_path)+1);

        char *file_name = get_fname(src_path);
        printf("fname - %s\n", file_name);

        idx++;
        if (argv[idx]==NULL){
            printf("mv:arguments missing\n");
        }
        
        if (getcwd(dest_path, PATH_MAX)==NULL){
            printf("mv:getcwd failed\n");
            exit(EXIT_FAILURE);
        }
        strncat(dest_path, "/", 1);
        strncat(dest_path, argv[idx], strlen(argv[idx]));
        strncat(dest_path, "/", 1);
        strncat(dest_path, file_name, strlen(file_name));

        printf("src- %s\n", src_path);
        printf("dest- %s\n", dest_path);
        if (rename(src_path, dest_path)<0){
            printf("mv:move failed\n");
            exit(EXIT_FAILURE);
        }
        idx++;
        memset(src_path, 0, PATH_MAX);
        memset(dest_path, 0, PATH_MAX);
        memset(src_name, 0, strlen(src_name));
    }
    if (idx==1){
        printf("mv:arguments missing\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}