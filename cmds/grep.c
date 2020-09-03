#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

int find_input_size(char *argv[]);

int check_file(char *fname, char *to_match, int flag){
    char *line=NULL;
    size_t lenght=0;

    FILE *file;
    file = fopen(fname, "r");
    if (file == NULL) {
        printf("grep: cannot open file\n");
        exit(EXIT_FAILURE);
    }
    while ((getline(&line, &lenght, file))!=-1){
        if (strstr(line, to_match)){
            if (flag){
                printf("%s: ", fname);
            }
            printf("%s", line);
        }
    }
    return 0;
}

int cmd_grep(char *argv[]){
    int argc = find_input_size(argv);
    int multiple_flag=0;
    if (argc>2){
        multiple_flag=1;
    }

    if (argv[1]==NULL){
        printf("grep: searchterm [file ...]\n");
        exit(EXIT_FAILURE);
    }
    
    char *to_match = argv[1];

    if (argv[2]==NULL){
        char *line=NULL;
        size_t lenght=0;
        while ((getline(&line, &lenght, stdin))!=-1){
            if (strstr(line, to_match)){
                printf("%s", line);
            }
        }
        exit(EXIT_SUCCESS);
    }


    int idx=2;
    while (argv[idx]!=NULL){
        check_file(argv[idx], to_match, multiple_flag);
        idx++;
    }
    return 0;
}