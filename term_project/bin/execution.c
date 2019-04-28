/* check the command and its arguments
   and then execute the correct command function */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "../headers/cmds.h"
#include "../headers/execute.h"

void execution(int argc, char *args[]){
    char *cmd = args[0];
    
    if(!strcmp(cmd, "pwd")) pwd(argc); // void pwd(argc)
    else if(!strcmp(cmd, "echo")) echo(args); // void echo(char *str)
    else if(!strcmp(cmd, "clear")) clear(); // void clear(void)
    else if(!strcmp(cmd, "cat")) cat(argc, args); // void cat(int argc, char *args[])
    else if(!strcmp(cmd, "rm")) rm(argc, args); // void rm(int argc, char *args[])
    else if(!strcmp(cmd, "mv")) mv(argc, args); // void mv(int argc, char *args[])
    else if(!strcmp(cmd, "cp")) cp(argc, args); // void copy(int argc, char *args[])
    else if(!strcmp(cmd, "hello")) hello(argc, args); // void hello(int argc, char *args[])
    else if(!strcmp(cmd, "mkdir")) makedir(argc, args); // void mkdir(int argc, char *args[])
    else if(!strcmp(cmd, "ls")) ls(argc, args); // void ls(int argc, char *args[])
    else printf("hysh: command not found: %s\n", cmd);

    // kill a child process for (looks like) overwriting
    exit(0);
}
