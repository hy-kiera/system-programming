/* mkdir : make a directory */
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#include "../headers/cmds.h"

static void make_path(const char *path);

void makedir(int argc, char *args[]){
    int status;
    int i;

    if (argc < 2)fprintf(stderr, "%s : no arguments\n", args[0]);
    
    if (argc >= 2){
        // no option
        if (args[1][0] != 45){ // "-" : 45(ascii code)
            for(i = 1; i < argc; i++){
                if (!mkdir(args[i], 0755)) fprintf(stderr, "mkdir: already exists\n");
            }
        }
        // with option
        else {
            // create directory hirarichy
            if (!strcmp(args[1], "-p")){
                for(i = 2; i < argc; i++){
                    make_path(args[i]);
                    if (status == -1) fprintf(stderr, "mkdir: no such file or directory\n");
                }
            }
            // make a directory and move to it.
            else if (!strcmp(args[1], "-C")){
                if (!mkdir(args[2], 0755)) fprintf(stderr, "mkdir: already exists\n");
                else{
                    if (chdir(args[3]) != 0) fprintf(stderr, "cd: %s: no such file or directory\n", args[3]);
                }
            }
            // show help
            else if (!strcmp(args[1], "--help") || !strcmp(args[1], "-h")){
                printf("usage : mkdir [options] [directory name ...]\n\nmake directories.\n\n[options]\n\n-p : If the parent directories don't exist, this command creates them.\n\n-C : Make a directory and move to it.\n\n--help, -h : Show help.\n");
            }
            else{
                // wrong option
                fprintf(stderr, "-hysh: %s: %s: invalid signal specification", args[0], args[1]);
            }
        }
    }
}

static void make_path(const char *path){
    int status;
    
    // drwxr-xr-x
    if ((status = mkdir(path, 0755)) == 0){
        return;
    }

    // file exist
    if (errno == EEXIST){
        struct stat st;

        if (stat(path, &st) < 0) perror("stat");
        if (!S_ISDIR(st.st_mode)){ // check it is a directory
            fprintf(stderr, "file exists but is not a directory: %s\n", path);
        }
        return;
    }

    // no such file or directory
    else if (errno == ENOENT){
        char *parent_path = strdup(path); // duplicate path

        if (!parent_path) perror("strdup");

        char *last = parent_path + strlen(parent_path) - 1;

        while (*last == '.' && last != parent_path){
            *last-- = '\0';
        }

        // root directory
        if(!strcmp(parent_path, "/")){
            fprintf(stderr, "error: root directory is not a directory???\n");
        }

        char *sep = strrchr(parent_path, '/'); // find the last occurrence of c (converted to a character) in string

        if (!sep){
            fprintf(stderr, "error: current directory is not a directory???\n");
        }
        // root directory
        else if (sep == parent_path){
            fprintf(stderr, "error: root directory is not a directory???\n");
        }
        *sep = '\0';
        make_path(parent_path); // call recursive

        if ((status = mkdir(path, 0755)) < 0) perror(path);
        return;
    }
    else{
        perror(path);
    }
}
