#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>

#define SHELL_NAME "fish"
#define MAX_LEN_CMD 128


int read_input(char *input_str, char *parsed_input[]){
    /*
    This function reads input and splits them on spaces using strtok function
    and returns the length of array created 
    */
    const char delim[]=" ";
    char *token;

    if (fgets(input_str, MAX_LEN_CMD, stdin)==NULL){
        printf("Error taking input");
        exit(EXIT_FAILURE);
    };
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