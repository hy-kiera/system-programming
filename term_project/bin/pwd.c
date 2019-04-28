/* pwd : print the name of the current(working) directory */
#include <unistd.h> // char *getcwd(char *buf, size_t size);
#include <stdio.h>
#include <limits.h>

#include "../headers/cmds.h"

void pwd(int argc){
    char cwd[PATH_MAX];
    if(argc == 1){
        // get current working directory
        if(getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("%s\n", cwd);
        }
        else {
            perror(cwd);
        }
    }
    else {
        fprintf(stderr, "pwd: too many arguments\n");
    }
}
