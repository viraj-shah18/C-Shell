#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

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


int is_parent_cmd(char *input_array[]){
    int parent_cmd=0;
    for (int a=0;a<total_parent_cmds;a++){
        if (strcmp(input_array[0], list_of_parent[a])==0){
            // printf("Parent cmd found\n");
            parent_cmd=1;
            (parent_fn_pointer[a])(input_array);
        }
    }
    return parent_cmd;
}

int is_child_cmd(char *input_array[]){
    int child_cmd=0;
    char *command=input_array[0];
    for (int a=0;a<total_cmds;a++){
        if (strcmp(command, list_of_cmd[a])==0){
            // printf("Cmd found\n");
            child_cmd=1;
            (cmd_fn_pointer[a])(input_array);
        }
    }
    return child_cmd;

}

int run_background(int input_size, char *input_array[]){
    int run_background=0;
    if (strcmp("&", input_array[input_size-1])==0){
        run_background=1;
    }
    return run_background;
}

int run_builtin(char *input_array[]){
    int builtin=1;
    printf("trying to use inbuilt binaries\n");
    if (execvp(input_array[0], input_array)<0){
        builtin=0;
        printf("Command not known. Please enter valid command\nExec failed\n");
    }
    return builtin;

}


int cmd_exit(char *argv[]){
    exit(EXIT_SUCCESS);
}