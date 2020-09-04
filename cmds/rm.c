#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

#ifndef PATH_MAX
#define PATH_MAX 1024
#endif

int delete_files(char *file_path){
    /*
    This function takes absolute path as argument and deletes that file
    */
    int rc = unlink(file_path);
    if (rc<0){
        printf("rm: file deletion failed\n");
    }
    return 0;
}


int delete_dir(char *dir_path){
    /*
    to delete a directory, first need to remove all its contents
    this funntion loops over all contents of the directory
    if that is directory, recusively calls this function
    else calls delete_file function
    */

    DIR *open_dir;
    struct dirent *read_dir;
    // opens the directory
    if ((open_dir=opendir(dir_path))==NULL){
        printf("rm:error opening directory\n");
        exit(EXIT_FAILURE);
    }

    // looping over all the contents of that directory 
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

        // checking if file is current dir (.) or parent directory (..)
        // and skipping those
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
    // in the end, now dir is empty and can be removed using rmdir
    if (rmdir(dir_path)<0){
        printf("rm:unable to delete the directory\n");
        exit(EXIT_FAILURE);
    }
    return 0;
}

int cmd_rm(char *argv[]){
    /*
    This is my implementation of rm command
    it gets absolute path of the directories to be deleted
    and calls the delete_dir and delete_file functions

    Usage example
    >> rm test.py
    >> rm test.py test2.py
    >> rm -r t1
    >> rm -r t1 -r t2
    >> rm -r t1 test.py
    */
    
    struct stat file_info;
    char path[PATH_MAX];
    // gets the absolute path of working dir
    if (getcwd(path, PATH_MAX)==NULL){
        printf("path error\n");
        exit(EXIT_FAILURE);
    }

    // looping over all the arguments
    int idx=1;
    while(argv[idx]!=NULL){
        int is_dir=0;
        // checking for recursive flag
        if (strcmp(argv[idx], "-r")==0){
            idx++;
            is_dir=1;
        }

        if (argv[idx]==NULL){
            printf("rm:Argument missing\n");
            exit(EXIT_FAILURE);
        }

        // using stat to find the file type
        char *name = argv[idx];
        // printf("%s\n", name);
        int rc=stat(name,&file_info);
        if (rc<0){
            printf("rm: stat failed\n");
            exit(EXIT_FAILURE);
        }
        // checking if it is directory and -r flag is passed
        if (S_ISDIR(file_info.st_mode) && is_dir){
            char test_path[PATH_MAX];
            strncpy(test_path, path, strlen(path)+1);
            strncat(test_path, "/", 1);
            strncat(test_path, name, strlen(name));
            delete_dir(test_path);
        }
        // checking if it is not a directory and -r flag is not passed
        else if (!S_ISDIR(file_info.st_mode) && !is_dir){
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