/* check the command and its arguments
   and then execute the correct command function */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "../headers/cmds.h"
#include "../headers/execute.h"

void execution(int argc, char *cmd, char *args[]){
//    printf("args : %s %s\n\n", cmd, args[0]);
    if(!strcmp(cmd, "pwd")) pwd(argc); // void pwd(argc)
    else if(!strcmp(cmd, "echo")) echo(args); // void echo(char *str)
    else if(!strcmp(cmd, "clear")) clear(); // void clear(void)
    else if(!strcmp(cmd, "cat")) cat(argc, args); // void cat(int argc, char *args[])
    else if(!strcmp(cmd, "cd")) cd(argc, args); // void cd(int argc, char *args[])
    else printf("hysh: command not found: %s\n", cmd);
    // kill a child process for overwriting
    exit(0);
}
