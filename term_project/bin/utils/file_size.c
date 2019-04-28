#include <sys/stat.h>

#include "../../headers/utils.h"

// get file size
long int file_size(const char *file_name){
    struct stat st;

    if (stat(file_name, &st) == 0)
        return (st.st_size);
    else
        return -1;
}