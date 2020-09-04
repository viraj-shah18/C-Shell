#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

int find_input_size(char *argv[]);

int check_file(char *fname, char *to_match, int flag){
    /*
    takes filename, pattern and flag storing if there are multiple files
    
    function tries opening the file 
    and checks line by line if pattern is a substring of that line

    */
    char *line=NULL;
    size_t lenght=0;
    
    // opening the file
    FILE *file;
    file = fopen(fname, "r");
    if (file == NULL) {
        printf("grep: cannot open file\n");
        exit(EXIT_FAILURE);
    }

    // read line by line
    while ((getline(&line, &lenght, file))!=-1){
        // checking whether that pattern is a substring of that line 
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
    /*
    This is my implementation of grep command
    It validates the arguments and aggregates all argv
    and then passes file to check_file function 

    Usage example
    >> grep time test.py test2.py
    >> grep time 
    
    */

    int argc = find_input_size(argv); // in the helper.c file
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