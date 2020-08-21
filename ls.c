#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>

#define SHELL_NAME "fish"

// stat
// isdir
// print

void read_input();
void ps(char* argv[]);
void ls_print(int argc, char *argv[]);
void read_dir(int argc, char *argv[]);

int main(){
    printf("%s>", SHELL_NAME);
    // char argv[];
    
    // ps();
    return 0;
}


void read_input(){
    char *buffer;
    size_t bufsize = 128;
    size_t input_size;


    buffer=(char *)malloc(bufsize*sizeof(char));
    input_size = getline(&buffer, &bufsize,stdin);
    

}

void ps(char* argv[]){
    int rc=fork();
    if (rc<0){
        printf("Command ps cannot be executed");
        return;
    }else if (rc==0)
    {
        // argv will be of form ["ps", "-p", "pid"]
        execl("/usr/bin/ps",argv);
    }else
    {
        int wc = wait(NULL);
        printf("ps ran successfully");
    }
}
