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
int create_daemon(char *path);

int is_parent_cmd(char *input_array[]);
int is_child_cmd(char *input_array[]);
int run_background(int input_size, char *input_array[]);
int run_builtin(char *input_array[]);
int cmd_exit(char *argv[]);

int main(){
    while (1){
        // printf("%s > ", SHELL_NAME);
        int input_size;
        char *parsed_input[MAX_LEN_CMD];

        input_size = read_input(parsed_input);
        if (input_size<0){
            continue;
        }

        // this is to slice the array to required input length and adding NULL as last element
        // printf("here");
        char *input_array[input_size+1];
        for (int idx=0;idx<input_size;idx++){
            // printf("pi - idx - %d value - %s\n", idx, parsed_input[idx]);
            input_array[idx] = parsed_input[idx];
            // printf("ia - idx - %d value - %s\n", idx, input_array[idx]);
        }
        input_array[input_size]=NULL;
        
        if (is_parent_cmd(input_array)){
            continue;
        }
        // TODO: change this
        int run_bg_flag=run_background(input_size, input_array);

        // printf("REached here");
        int rc=fork();
        if (rc<0){
            printf("Function main-Fork failed\n");
            return 0;
        }
        else if(rc==0){
            if (run_bg_flag==1){
                printf("%d\n", (int)getpid());
                input_array[input_size] = NULL;
                char *curr_path;
                if (getcwd(curr_path, PATH_MAX)<0){
                    printf("daemon:getcwd failed\n");
                }
                create_daemon(curr_path);
                // TODO: Write daemon function, use man 7 daemon
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
            if (run_bg_flag){
                run_bg_flag=0;
                continue;
            }
            else{
                wait(NULL);
            }
            // printf("teminal pid: %d\n", (int) getpid());
        }
    }
}