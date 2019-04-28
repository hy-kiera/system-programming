#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>

#include "../../headers/utils.h"

// return the file type
mode_t get_type(const char *path){
    struct stat file_info;

    if (stat(path, &file_info) < 0) perror(path);
    return file_info.st_mode;
}