#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>

#define SHELL_NAME "fish"
#define MAX_LEN_CMD 128
#define PATH_MAX 1024


// function declarations
int read_input(char *parsed_input[]);
int create_daemon();

int is_parent_cmd(char *input_array[]);
int is_child_cmd(char *input_array[]);
int run_background(int input_size, char *input_array[]);
int run_builtin(char *input_array[]);
int cmd_exit(char *argv[]);

int main(){
    while (1){
        int input_size;
        char *parsed_input[MAX_LEN_CMD];

        input_size = read_input(parsed_input);
        if (input_size<0){
            continue;
        }

        // this is to slice the array to required input length and adding NULL as last element
        char *input_array[input_size+1];
        for (int idx=0;idx<input_size;idx++){
            input_array[idx] = parsed_input[idx];
        }
        input_array[input_size]=NULL;
        
        if (is_parent_cmd(input_array)){
            continue;
        }

        int run_bg_flag=run_background(input_size, input_array);
        
        int rc=fork();
        if (rc<0){
            printf("main:fork failed\n");
            exit(EXIT_FAILURE);
        }
        else if(rc==0){
            // child process
            if (run_bg_flag==1){
                input_array[input_size] = NULL;
                create_daemon();
            }
            
            int child_cmd=is_child_cmd(input_array);
            
            // if not present in child command trying to run builtin bin files 
            if (!child_cmd){
                int builtin = run_builtin(input_array);
                if (!builtin){
                    exit(EXIT_FAILURE);
                }
            }
            exit(EXIT_SUCCESS);
        }
        else{
            // parent process
            if (run_bg_flag){
                run_bg_flag=0;
                continue;
            }
            else{
                wait(NULL);
            }
        }
    }
}