/* rm : remove files or directories */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

void rm(char *args[]);

int main(void){
    char *args[] = {"rm", "-h", "--help", "-r", "-ri"};
    rm(args);
    return 0;
}

void rm(char *args[]){
    if (!strcmp(args[1], "--help") || !strcmp(args[1], "-h")){
        printf("usage : rm [options] [file] <path>\n\nremove files or directories\n\n[options]\n\n-r : Attempt to remove the file hierarchy(directory) rooted in each file argument.\n\n-ri : Remove the file hierarchy and the user has been prompted for confirmation before each directory's contents are processed (as well as before the attempt is made to remove the directory).\n\n--help, -h : Show help.\n");
    }
    else if (!strcmp(args[1], "-r")){
    // remove directory
    // 디렉터리를 내용과 함께 삭제하기 위해서는 디렉터리 트리를 순회하며 내용을 하나씩 지운다.    
    }
}
