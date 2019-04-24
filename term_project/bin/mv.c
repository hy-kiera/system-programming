/* mv : moves one or more files or directories from one place to another */
#include <stdio.h>
#include <string.h>

void mv(char *args[]);
int do_move(char *old_file, char *new_file);

int main(void){
    int arg_num = 2; // arg_num = sizeof(args) / sizeof(char *);
    char *args[] = {"mv", "-h", "--help", "-C"};
    mv(arg_num, args);
    return 0;
}

void mv(int arg_num, char *args[]){
    if (arg_num != 3 || arg_num != 4){
        fprintf(stderr, "%s: wrong arguments\n", argv[0]);
    }

    // no option
    if (arg_num == 3){
        do_move(args[1], args[2]);
    }
    
    // with option
    if (arg_num == 4){
        if (!strcmp(args[1], "-C")){
            do_move(args[1], args[2]);
            // do_cd
        }
        else if (!strcmp(args[1], "--help") || !strcmp(args[1], "-h")){
            printf("usage : mv [options] <old_file>  <new_file>\n\nmoves one or more files or diectories from one place to another\n\n[options]\n\n-C : Move to the directory where a file is moved.\n\n--help, -h : Show help.\n");
        }
        else{
            // wrong option
            printf("-hysh: %s: %s: invalid signal specification", args[0], args[1]);
    }
}

int do_move(char *old_file, char *new_file){
    // the name of the file to be renamed and/or moved. 
    // yee gue yae an dae...:( an oum jik yie...
    if (rename(old_file, new_file) < 0){
        perror(old_file);
        exit(1);
    }
    exit(0);
}
