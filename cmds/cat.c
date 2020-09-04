#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#ifndef PATH_MAX
#define PATH_MAX 1024
#endif

int cmd_cat(char *argv[]){
    /*
    This is my implementation of cat command
    It validates the arguments and then uses relative path to open the file
    reads the file line by line and prints on the stdout. does work on multiple files

    Usage example
    >> cat test.py test2.py
    prints content of test.py
    prints content of test2.py
    */
    char path[PATH_MAX];

    if (argv[1]==NULL){
        printf("No files specified\n");
        exit(EXIT_FAILURE);
    }
    // to use relative path
    if (getcwd(path, PATH_MAX)==NULL){
        printf("path error\n");
        exit(EXIT_FAILURE);
    }

    int idx=1;
    while (argv[idx]!=NULL){
        FILE *curr_file;
        char *line=NULL;
        size_t lenght=0;
        curr_file=fopen(argv[idx], "r");
        if (curr_file==NULL){
            printf("%d", errno);
            printf("cat: cannot open file\n");
            exit(EXIT_FAILURE);
        }

        // reading line by line
        while ((getline(&line, &lenght, curr_file))!=-1){
            printf("%s", line);
        }
        fclose(curr_file);
        idx++;
    }
    return 0;
}