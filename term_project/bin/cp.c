/* cp : copy a file or a directory from one directory to another */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void copy(char *args[]);

int main(void){
    char *args[] = {"cp", "--help", "-h", "-r", "-C", "-m"};
    copy(args);
    return 0;
}

void copy(char *args[]){
    if (!strcmp(args[1], "--help") || !strcmp(args[1], "-h")){
        printf("usage : cp [options] [source file] [target file] <name>\n\ncopy a file or a directory from one directory to another\n\n[options]\n\n-r : If source file designates a file, cp copies the file. If source file designates a directory, cp copies the directory and the entire subtree connected at that point.\n\n-C : Move the directory where has the copied file, after coping source file.\n\n-m : copy a file renamed.\n\n--help, -h : Show help.\n");
    }
    else if (!strcmp(args[1], "-r")){
           
    }
    else{
        // wrong option
        printf("-hysh: %s: %s: invalid signal specification", args[0], args[1]);
    }
}
