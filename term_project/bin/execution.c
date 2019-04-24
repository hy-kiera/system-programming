/* check the command and its arguments
   and then execute the correct command function */
#include <string.h>

#include "../headers/cmds.h"
#include "../headers/execute.h"

void execution(char *cmd, char *args[]){
    printf("args : %s%s\n", cmd, args[0]);
    if(!strcmp(cmd, "pwd")) pwd(); // void pwd(void)
    if(!strcmp(cmd, "echo")) echo(args[1]); // void echo(char *str)
    if(!strcmp(cmd, "clear")) clear(); // void clear(void)
}
