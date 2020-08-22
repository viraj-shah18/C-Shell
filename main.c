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

int read_input(char *, char*[]);

int main(){


    while (1){
        printf("%s>", SHELL_NAME);
        int input_size;
        char *input_str[MAX_LEN_CMD];
        char *parsed_input[MAX_LEN_CMD];

        input_size = read_input(&input_str, parsed_input);

        char *input_array[input_size+1];
        for (int idx=0;idx<input_size;idx++){
            input_array[idx]=parsed_input[idx];
        }
        input_array[input_size]=NULL;

        int rc=fork();
        if (rc<0){
            printf("Main Fork failed\n");
            return 0;
        }
        else if(rc==0){
            char *function_call=input_array[0];
            // printf("%s", function_call);
            // printf("%d", input_size);
            int ec = execvp(function_call, input_array);
            if (ec<0){
                printf("Command not known. Please enter valid command\nExec failed\n");
            }
            // printf("NOT printed\n");
        }
        else{
            wait(NULL);
        }
    }
}


int read_input(char *input_str, char *parsed_input[]){
    /*
    This function reads input and splits them on spaces using strtok function
    */
    const char delim[]=" ";
    char *token;

    fgets(input_str, MAX_LEN_CMD, stdin);
    strtok(input_str, "\n");

    token = strtok(input_str, delim);
    int input_size=0;

    while (token!=NULL){
        parsed_input[input_size]=token;
        token=strtok(NULL, delim);
        input_size++;
    }
    return input_size;
}