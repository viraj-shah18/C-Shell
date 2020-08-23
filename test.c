#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(){
    char *a[]={"pwd", "ls", "y", "po", "ted"};
    int si = sizeof(a)/sizeof(a[0]);
    printf("%d", si);
    return 0;
}