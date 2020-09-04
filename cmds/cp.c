#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>

#ifndef PATH_MAX
#define PATH_MAX 1024
#endif

char *get_fname(char *src_path);

int cp_file(char *src_path, char *dest_path){
    char *line=NULL;
    size_t lenght=0;

    FILE *src_file;
    FILE *dest_file;
    src_file = fopen(src_path, "r");
    if (src_file == NULL) {
        printf("cp: cannot open file\n");
        exit(EXIT_FAILURE);
    }

    dest_file = fopen(dest_path,"w");
    if (dest_file== NULL) {
        printf("cp: cannot open file\n");
        exit(EXIT_FAILURE);
    }

    while ((getline(&line, &lenght, src_file))!=-1){
        fprintf(dest_file,"%s", line);
    }
    fclose(src_file);
    fclose(dest_file);
    return 0;
}

int cp_dir(char *src_path, char *dest_path){
    char *dir_name=get_fname(src_path);
    mkdir(dest_path, 0777);

    DIR *open_dir;
    struct dirent *read_dir;

    if ((open_dir=opendir(src_path))==NULL){
        printf("error opening source directory");
        exit(EXIT_FAILURE);
    }

    // looping to find all the files in the directory
    while ((read_dir=readdir(open_dir))!=NULL){

        // by default readdir prints all the hidden files + ".." + "."
        // all start with "."
        // so comparing the first letter to check whether it is "."
        if (read_dir->d_name[0] != '.') {
            char src_path_copy[strlen(src_path)+64];
            char dest_path_copy[strlen(dest_path)+64];
            strncpy(src_path_copy, src_path, strlen(src_path));
            printf("here\n");
            strncat(src_path_copy, "/", 1);
            strncat(src_path_copy, read_dir->d_name, strlen(read_dir->d_name));
            strncpy(dest_path_copy, dest_path, strlen(dest_path)+1);
            strncat(dest_path_copy, "/",1);
            strncat(dest_path_copy, read_dir->d_name, strlen(read_dir->d_name));
            // printf("%s\n", src_path_copy);
            // printf("%s\n", dest_path_copy);
            struct stat check_dir;
            int rc=stat(src_path_copy,&check_dir);
            if (rc<0){
                printf("ls:stat command failed\n");
                exit(EXIT_FAILURE);
            }
            if (!S_ISDIR(check_dir.st_mode)){
                // printf("here\n");
                cp_file(src_path_copy, dest_path_copy);
            }
            memset(src_path_copy, 0, strlen(src_path_copy));
            memset(dest_path_copy, 0, strlen(dest_path_copy));
        }
    }
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
        strncat(src_path, "/", 1);
        strncat(src_path, argv[idx], strlen(argv[idx]));
        printf("src - %s\n", src_path);
        src_name=get_fname(src_path);
        
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
        strncat(dest_path, "/", 1);
        strncat(dest_path, src_name, strlen(src_name));
        printf("dest - %s\n", dest_path);
        
        struct stat file_info;
        int rc=stat(src_path,&file_info);
        if (rc<0){
            printf("cp: stat failed\n");
            exit(EXIT_FAILURE);
        }

        if (S_ISDIR(file_info.st_mode) && r_flag){
            cp_dir(src_path, dest_path);
        }

        else if (!S_ISDIR(file_info.st_mode) && !r_flag){
            cp_file(src_path, dest_path);
        }
        else{
            printf("cp:invalid arguments\n");
            exit(EXIT_FAILURE);
        }

        
        
        
        idx++;


    }    
    if (idx==1){
        printf("cp:missing arguments\n");
        exit(EXIT_FAILURE);
    }   
    return 0;
}