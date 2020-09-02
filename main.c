#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>

#define SHELL_NAME "fish"
#define MAX_LEN_CMD 128


// function declarations
int read_input(char *parsed_input[]);
int create_daemon();

int is_parent_cmd(char *input_array[]);
int is_child_cmd(char *input_array[]);
int run_background(int input_size, char *input_array[]);

int main(){
    while (1){
        printf("%s> ", SHELL_NAME);
        int input_size;
        char *parsed_input[MAX_LEN_CMD];

        input_size = read_input(parsed_input);

        // this is to slice the array to required input length and adding NULL as last element
        char *input_array[input_size+1];
        for (int idx=0;idx<input_size;idx++){
            input_array[idx]=parsed_input[idx];
        }
        input_array[input_size]=NULL;
        
        if (is_parent_cmd(input_array)){
            continue;
        }

        int run_bg_flag=run_background(input_size, input_array);

        // printf("REached here");
        int rc=fork();
        if (rc<0){
            printf("Function main-Fork failed\n");
            return 0;
        }
        else if(rc==0){
            if (run_background==1){
                printf("%d\n", (int)getpid());
                create_daemon();
                // TODO: Write daemon function, use man 7 daemon
                input_array[input_size-1] = NULL;
            }
            
            int child_cmd=is_child_cmd(input_array);
            
            if (!child_cmd){
                int builtin = run_builtin(input_array);
                if (!builtin){
                    exit(EXIT_FAILURE);
                }
            }
            exit(EXIT_SUCCESS);
        }
        else{
            wait(NULL);
            // if (run_background){
            //     run_background=0;
            //     continue;
            // }
            // else{
            // }
            // printf("teminal pid: %d\n", (int) getpid());
        }
    }
}