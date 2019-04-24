/* pwd : print the name of the current(working) directory */
#include <unistd.h> // char *getcwd(char *buf, size_t size);
#include <stdio.h>
#include <limits.h>

#include "../headers/cmds.h"

void pwd(void){
    char cwd[PATH_MAX];
    // get current working directory
    if(getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s", cwd);
    }
    else {
        perror("pwd error");
    }
}
