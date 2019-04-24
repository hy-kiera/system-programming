/* mkdir : make a directory */
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>

void makedir(int argc, char *args[]);
static void make_path(const char *path);

int main(void){
    int argc = 3;
    char *args[] = {"mkdir", "-p", "a/b/c"};
    makedir(argc, args);
}

void makedir(int argc, char *args[]){
    int status;
    int i;

    if (argc < 2)fprintf(stderr, "%s : no arguments\n", args[0]);
    
    if (argc >= 2){
        // no option
        if (args[1][0] != 45){ // "-" : 45(ascii code)
            for(i = 1; i < argc; i++){
                status = mkdir(args[i], 0755);
            }
        }
        // with option
        else {
            if (!strcmp(args[1], "-p")){
                for(i = 2; i < argc; i++){
                    printf("i : %d\n", i);
                    make_path(args[i]);
                    if (status == -1) fprintf(stderr, "mkdir: no such file or directory\n");
                }
            }
            else if (!strcmp(args[1], "-C")){
                if (argc != 3) fprintf(stderr, "%s: too many arguments", args[0]);
                else{
                    // cd
                }
            }
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
    
    if ((status = mkdir(path, 0755)) == 0){
        return;
    }

    // file exist
    if (errno == EEXIST){
        struct stat st;

        if (stat(path, &st) < 0) perror("stat");
        if (!S_ISDIR(st.st_mode)){
            fprintf(stderr, "file exists but is not a directory: %s\n", path);
            // exit(1);
        }
        return;
    }

    // no such file or directory
    else if (errno == ENOENT){
        char *parent_path = strdup(path);

        if (!parent_path) perror("strdup");

        char *last = parent_path + strlen(parent_path) - 1;

        while (*last == '.' && last != parent_path){
            *last-- = '\0';
        }

        if(!strcmp(parent_path, "/")){
            fprintf(stderr, "error: root directory is not a directory???\n");
            // exit(1);
        }

        char *sep = strrchr(parent_path, '/');

        if (!sep){
            fprintf(stderr, "error: current directory is not a directory???\n");
            // exit(1);
        }
        else if (sep == parent_path){
            fprintf(stderr, "error: root directory is not a directory???\n");
            // exit(1);
        }
        *sep = '\0';
        make_path(parent_path);
        printf("MAKE DIR\n");
        if ((status = mkdir(path, 0755)) < 0) perror(path);
        return;
    }
    else{
        perror(path);
        //  exit(1);
    }
}
