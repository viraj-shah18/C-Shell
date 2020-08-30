#include <string.h>
#include <limits.h>
#include <errno.h>

int cmd_cd(char *argv[]){
    printf("my cd\n");
    char curr_path[PATH_MAX];
    // checking for first argument
    if (argv[1]==NULL){
        printf("Path not specified\n");
        exit(EXIT_FAILURE);
    }
    if (argv[1][0]!='/'){
        if (getcwd(curr_path, PATH_MAX)==NULL){
            printf("cd:getcwd failed\n");
        };
        strncat(curr_path, "/", 1);
        strncat(curr_path, argv[1], strlen(argv[1])+1);
    }
    else{
        strncpy(curr_path, argv[1], strlen(argv[1])+1);
    }
    printf("%s\n", curr_path);
    int rc=chdir(curr_path);
    printf("%d\n", errno);
    if (rc<0){
        // if the path is not correct
        printf("Changing Directories failed - Directory not found\n");
    }
    memset(curr_path, 0, PATH_MAX);
    return 0;
}