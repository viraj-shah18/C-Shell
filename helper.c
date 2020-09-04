#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

#ifndef MAX_LEN_CMD
#define MAX_LEN_CMD 128
#endif

#ifndef PATH_MAX
#define PATH_MAX 1024
#endif

int cmd_pwd(char *argv[]);
int cmd_ls(char *argv[]);
int cmd_mkdir(char *argv[]);
int cmd_chmod(char *argv[]);
int cmd_cat(char *argv[]);
int cmd_rm(char *argv[]);
int cmd_mv(char *argv[]);
int cmd_grep(char *argv[]);
int cmd_cp(char *argv[]);

int cmd_exit(char *argv[]);
int cmd_cd(char *argv[]);

//for comparing with the input command with defined commands
char *list_of_cmd[] = {"ls", "pwd", "mkdir","chmod", "cat","rm", "mv", "grep", "cp"};
char *list_of_parent[]={"exit", "cd"};

//using pointer to function to run the command entered
int (*cmd_fn_pointer[]) (char **)={&cmd_ls, &cmd_pwd, &cmd_mkdir,&cmd_chmod, &cmd_cat,&cmd_rm, &cmd_mv, &cmd_grep, &cmd_cp};
int (*parent_fn_pointer[]) (char **)={&cmd_exit, &cmd_cd};

int total_cmds = sizeof(list_of_cmd)/sizeof(list_of_cmd[0]);
int total_parent_cmds = sizeof(list_of_parent)/sizeof(list_of_parent[0]);


int read_input(char *parsed_input[]){
    /*
    This function reads input and splits them on spaces using strtok function
    and returns the length of array created 
    */
    const char delim[]=" ";
    char *token;
    char *input_str;

    input_str = readline("> ");
    if (strlen(input_str)<1){
        parsed_input[0]=NULL;
        return 1;
    }
    add_history(input_str);
    // printf("%s\n", input_str);
    strtok(input_str, "\n");    // this is to remove the last "\n" character from the input

    // tokenising the input using " " as delimiter
    token = strtok(input_str, delim);
    int input_size=0;

    while (token!=NULL){
        parsed_input[input_size]=token;
        token=strtok(NULL, delim);
        input_size++;
    }

    return input_size;
}



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
    // printf("%s\n", input_array[0]);
    if (execvp(input_array[0], input_array)<0){
        builtin=0;
        printf("Command not known. Please enter valid command\nExec failed\n");
    }
    return builtin;
}


int cmd_exit(char *argv[]){
    exit(EXIT_SUCCESS);
}

int find_input_size(char *argv[]){
    int length=0;
    while (argv[length]!=NULL){
        length++;
    }
    return length;
}

void reverseStr(int str_size, char str[]){ 
    for (int i=0; i<str_size/2; i++){
        char temp=str[i];
        str[i]=str[str_size-i-1];
        str[str_size-i-1]=temp;
    }
}

char *get_fname(char *src_path){
    char src_path_copy[PATH_MAX];
    strncpy(src_path_copy, src_path, strlen(src_path)+1);
    reverseStr(strlen(src_path_copy), src_path_copy);
    char *file_name = strtok(src_path_copy, "/");
    reverseStr(strlen(file_name), file_name);
    return file_name;
}