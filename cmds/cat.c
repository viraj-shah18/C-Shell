#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

int cmd_cat(char *argv[]){
    char path[PATH_MAX];

    if (argv[1]==NULL){
        printf("No files specified\n");
        exit(EXIT_FAILURE);
    }
    // to get current working directory for complete path
    if (getcwd(path, PATH_MAX)==NULL){
        printf("path error\n");
        exit(EXIT_FAILURE);
    }

    int idx=1;
    while (argv[idx]!=NULL){
        FILE *curr_file;
        char full_path[PATH_MAX];
        strncpy(full_path, path, strlen(path)-1);
        strncat(full_path, "/",1);
        strncat(full_path, argv[idx],strlen(argv[idx]));
        curr_file=fopen(argv[idx], "r");
        if (curr_file==NULL){
            printf("%d", errno);
            printf("cat: cannot open file\n");
            exit(EXIT_FAILURE);
        }

        // basic reading char by char
        // TODO: read specific buffer size in 1 go
        char curr_char;
        while ((curr_char=fgetc(curr_file))!=EOF){
            printf("%c", curr_char);
        }
        fclose(curr_file);
        idx++;
    }
    return 0;
}