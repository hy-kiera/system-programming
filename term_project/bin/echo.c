/* echo : output the strings it is being passed as arguments */
#include <stdio.h>
#include <stdlib.h> // getenv()

void echo(char *str){
    // check str is a string or a environment variable
    if(str[0] != 36){ // "$" : 36(ascii code)
        printf("%s\n", str);
    }
    else { // echo a environment variable
        char *pathvar, *var;
        var = str + 1; // extract the substring after $
        pathvar = getenv(var); // get the environment variable
        printf("%s\n", pathvar);
    }
}
