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

int cmd_pwd(char *argv[]);
int cmd_ls(char *argv[]);
int cmd_mkdir(char *argv[]);
int cmd_chmod(char *argv[]);
int cmd_cat(char *argv[]);
int cmd_rm(char *argv[]);
int cmd_mv(char *argv[]);

int cmd_exit(char *argv[]);
int cmd_cd(char *argv[]);

//for comparing with the input command with defined commands
char *list_of_cmd[] = {"ls", "pwd", "mkdir","chmod", "cat","rm", "mv"};
char *list_of_parent[]={"exit", "cd"};

//using pointer to function to run the command entered
int (*cmd_fn_pointer[]) (char **)={&cmd_ls, &cmd_pwd, &cmd_mkdir,&cmd_chmod, &cmd_cat,&cmd_rm, &cmd_mv};
int (*parent_fn_pointer[]) (char **)={&cmd_exit, &cmd_cd};

int total_cmds = sizeof(list_of_cmd)/sizeof(list_of_cmd[0]);
int total_parent_cmds = sizeof(list_of_parent)/sizeof(list_of_parent[0]);

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
        //compare parent processes here
        for (int a=0;a<total_parent_cmds;a++){
            if (strcmp(input_array[0], list_of_parent[a])==0){
                // printf("Parent cmd found\n");
                (parent_fn_pointer[a])(input_array);
                // exit(EXIT_SUCCESS);
            }
        }
        // printf("REached here");
        int rc=fork();
        if (rc<0){
            printf("Function main-Fork failed\n");
            return 0;
        }
        else if(rc==0){
            char *command=input_array[0];
            for (int a=0;a<total_cmds;a++){
                if (strcmp(command, list_of_cmd[a])==0){
                    // printf("Cmd found\n");
                    (cmd_fn_pointer[a])(input_array);
                }
            }
            exit(EXIT_SUCCESS);
        }
        else{
            wait(NULL);
        }
    }
}

int cmd_exit(char *argv[]){
    exit(EXIT_SUCCESS);
}