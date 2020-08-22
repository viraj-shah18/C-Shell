#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>

#define SHELL_NAME "fish"
#define MAX_LEN_CMD 128
#define BASE_PATH_BIN "/usr/bin/"

int read_input();
// void ps(int argc, char* argv[]);
// void ls_print(int argc, char *argv[]);
// void read_dir(int argc, char *argv[]);

int main(){
    printf("%s>", SHELL_NAME);
    int input_size;
    char *input_str[MAX_LEN_CMD];
    char **parsed_input[MAX_LEN_CMD];

    input_size = read_input(&input_str, &parsed_input);

    char **input_array[input_size];
    for (int idx=0;idx<input_size;idx++){
        input_array[idx]=parsed_input[idx];
    }

    int rc=fork();
    if (rc<0){
        printf("Main Fork failed\n");
        return;
    }
    else if(rc==0){
        printf("Child here\n");
        printf("%s", input_array[0]);
        char *path;//=BASE_PATH_BIN+*input_array;
        printf("%s", path);
        //child
    }
    else{
        wait(NULL);
        printf("child process completed\n");
    }
    return 0;
}


int read_input(char *input_str, char **parsed_input){
    /*
    This function reads input and splits them on spaces using strtok function
    */
    
    const char delim[2]=" ";
    char *token;

    fgets(input_str, MAX_LEN_CMD, stdin);

    token = strtok(input_str, delim);
    int input_size=0;

    while (token!=NULL){
        parsed_input[input_size]=token;
        token=strtok(NULL, delim);
        input_size++;
    }
    parsed_input[input_size]=NULL;
    return input_size;
}

// void ps(int argc, char* argv[]){
//     int rc=fork();
//     if (rc<0){
//         printf("Command ps cannot be executed");
//         return;
//     }else if (rc==0)
//     {
//         // argv will be of form ["ps", "-p", "pid"]
//         execl("/usr/bin/ps",argv);
//     }else
//     {
//         int wc = wait(NULL);
//         printf("ps ran successfully");
//     }
// }
