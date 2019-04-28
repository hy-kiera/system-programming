/* echo : output the strings it is being passed as arguments */
#include <stdio.h>
#include <stdlib.h> // getenv()

#include "../headers/cmds.h"

void echo(char *str[]){
    int i = 1;
    char *pathvar, *var;
    
    // check str is a string or a environment variable
    if(str[1][0] != 36){ // "$" : 36(ascii code)
        while(str[i] != NULL){
            printf("%s ", str[i]);
            i++;
        }
        printf("\n");
    }
    else { // echo a environment variable
        var = str[1] + 1; // extract the substring after $
        pathvar = getenv(var); // get the environment variable
        printf("%s\n", pathvar);
    }
}
