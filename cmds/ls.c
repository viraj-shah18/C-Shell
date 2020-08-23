#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>

int cmd_ls(char *argv[]){
    printf("Hello this new ls command\n");
    char *ls_dir[32];
    struct stat file_info;
    DIR *open_dir;
    struct dirent *read_dir;

    // to find the number of directory present in input
    int i=1;
    if (argv[1]==NULL){
        ls_dir[0]=".";
        ls_dir[1]= NULL;
    }
    else{
        while (argv[i]!=NULL){
            ls_dir[i-1]=argv[i];
            i++;
        }
        ls_dir[i-1]=NULL;
    }

    int idx=0;
    while(ls_dir[idx]!=NULL){
        int rc=stat(ls_dir[idx],&file_info);
        if (rc<0){
            printf("ls command failed\n");
            exit(EXIT_FAILURE);
        }

        // checking if the ls is applied to a directory or not
        if (S_ISDIR(file_info.st_mode)){
            // If there are more than 1 directories in input, printing the name of directory
            if(i>2 && idx<i-1){
                printf("Directory Name - %s\n", ls_dir[idx]);
            }

            if ((open_dir=opendir(ls_dir[idx]))==NULL){
                printf("Error opening directory");
                exit(EXIT_FAILURE);
            }

            // looping to find all the files in the directory
            while ((read_dir=readdir(open_dir))!=NULL){

                // by default readdir prints all the hidden files + ".." + "."
                // all start with "."
                // so comparing the first letter to check whether it is "."
                if (read_dir->d_name[0] != '.') {
                    printf("%s\n", read_dir->d_name);
                }
            }
        }

        // if the input is not directory then just printing the file name
        else{
            printf("%s\n", ls_dir[idx]);
        }
        idx++;
        
        // adds the new line when there are several input directories
        if (i>2 && idx<i-1){
            printf("\n");
        }
    }
    return 0;
}