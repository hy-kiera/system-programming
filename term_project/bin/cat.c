/* cat : concatenate and print files */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "../headers/cmds.h"

#define BUF_SIZE 2048

static void do_cat(const char *path);
static void die(const char *s);

void cat(int argc, char *args[]){
    int i;
    // check 'cat' get argements needed
    if(argc < 2){
        fprintf(stderr, "%s : file name not given\n", args[1]);
        // exit(1);
    }
    else{
        for(i = 1; i < argc; i++){
        do_cat(args[i]);
        }
    }
    // exit(0);
}

static void do_cat(const char *path){
    int fd, n;
    unsigned char buf[BUF_SIZE];

    fd = open(path, O_RDONLY); // file descriptor
    if(fd < 0) die(path); // the file donot exist
    for(;;){
        n = read(fd, buf, sizeof(buf));
        if(n < 0) die(path); // cannot read the file
        if(n == 0) break; // finish reading the file
        if(write(STDOUT_FILENO, buf, n) < 0) die(path); // read the file with error detection
    }
    if(close(fd) < 0) die(path);
}

static void die(const char *s){
    perror(s);
    // exit(1);
}
