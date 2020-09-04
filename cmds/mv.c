#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>

#ifndef PATH_MAX
#define PATH_MAX 1024
#endif

// from helper.c
char *get_fname(char *src_path);

int cmd_mv(char *argv[]){
    /*
    This is my implementation of mv command
    it gets absolute path of the directories of src and dest
    appends src file name at the end of dest and renames the path of src files

    Usage example
    >> mv test.py t1
    >> mv test.py t1 test2.py t2
    >> mv t1 t2
    >> mv t1/11 ..
    */

    // looping over all args
    int idx=1;
    while (argv[idx]!=NULL){
        char src_path[PATH_MAX];
        char dest_path[PATH_MAX];

        char src_name[strlen(argv[idx])];
        // absolute path of working directory
        if (getcwd(src_path, PATH_MAX)==NULL){
            printf("mv:getcwd failed\n");
            exit(EXIT_FAILURE);
        }
        strncat(src_path, "/", 1);
        strncat(src_path, argv[idx], strlen(argv[idx]));

        char src_path_copy[PATH_MAX];
        strncpy(src_path_copy, src_path, strlen(src_path)+1);

        // getting the file name that needs to be appended in dest path
        char *file_name = get_fname(src_path);
        // printf("fname - %s\n", file_name);

        idx++;
        if (argv[idx]==NULL){
            printf("mv:arguments missing\n");
        }
        // absolute path of dest folder
        if (getcwd(dest_path, PATH_MAX)==NULL){
            printf("mv:getcwd failed\n");
            exit(EXIT_FAILURE);
        }
        strncat(dest_path, "/", 1);
        strncat(dest_path, argv[idx], strlen(argv[idx]));
        strncat(dest_path, "/", 1);
        strncat(dest_path, file_name, strlen(file_name));

        // printf("src- %s\n", src_path);
        // printf("dest- %s\n", dest_path);
        if (rename(src_path, dest_path)<0){
            printf("mv:move failed\n");
            exit(EXIT_FAILURE);
        }
        idx++;
        // clearing all else could interfere with nect arguments
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