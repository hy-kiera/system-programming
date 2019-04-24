/* cd : change the current working directory */
#include <unistd.h>
#include <stdio.h>

void cd(int argc, char *args[]){
    if(argc <= 2){
        // chdir() : makes pathname your new working directory
        printf("argc : %d, args : %s\n", argc, args[1]);
        if(chdir(args[1])){
            fprintf(stderr, "cd: no such file or directory: %s\n", args[1]);
        }
    }
    else {
        fprintf(stderr, "cd: string not in pwd: %s\n", args[1]);
    }
}
