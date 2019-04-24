/* mv : moves one or more files or directories from one place to another */
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

void mv(int argc, char *args[]);
void do_rename(char *old_file, char *new_file);
void do_move(char *file, char *new_path);

// return the file type
mode_t getType(const char *path){
    struct stat file_info;
    stat(path, &file_info);
    return file_info.st_mode;
}

int main(void){
    int argc = 3; // argc = sizeof(args) / sizeof(char *);
    char *args[] = {"mv", "abc.txt", "test", "-C"};
    mv(argc, args);
    return 0;
}

void mv(int argc, char *args[]){
    int stMode;
    int is_dir;
    
    if (argc < 2) fprintf(stderr, "%s : no arguments\n", args[0]);
    if (argc != 3 && argc != 4){
        fprintf(stderr, "%s: wrong arguments\n", args[0]);
    }

    // no option
    if (argc == 3){
        stMode = getType(args[2]);
        is_dir = S_ISDIR(stMode); // returns non-zero if the file is a directory
        
        // check renaming or moving
        if(is_dir){
            // move
            do_move(args[1], args[2]);
        }
        else{
            // rename
            do_rename(args[1], args[2]);
        }
    }
   
    stMode = getType(args[3]);
    is_dir = S_ISDIR(stMode);
    // with option
    if (argc == 4 && is_dir){
        if (!strcmp(args[1], "-C")){
            do_move(args[2], args[3]);
            // cd args[2]
        }
        else if (!strcmp(args[1], "--help") || !strcmp(args[1], "-h")){
            printf("usage : mv [options] <old_file>  <new_file>\n\nmoves one or more files or diectories from one place to another\n\n[options]\n\n-C : Move to the directory where a file is moved.\n\n--help, -h : Show help.\n");
        }
        else{
            // wrong option
            fprintf(stderr, "-hysh: %s: %s: invalid signal specification", args[0], args[1]);
        }
    }
}

// get file size
long int file_size(const char *file_name){
    struct stat st; // declare stat variable
    
    if (stat(file_name,&st) == 0)
        return (st.st_size);
    else
        return -1;
}

void do_move(char *file, char *new_path){
    FILE *fp, *new_fp;
    char new_file[256];
    char buffer[file_size(file)];

    strcpy(new_file, new_path);
    strcat(new_file, "/");
    strcat(new_file, file);

    fp = fopen(file, "r"); // open file for input operations. The file must exist.
    new_fp = fopen(new_file, "w+"); // create an empty file and open it for update (both for input and output). If a file with the same name already exists its contents are discarded and the file is treated as a new empty file.
   
    fread(buffer, file_size(file) + 1, 1, fp); // read data from file
    fwrite(buffer, 1, sizeof(fp), new_fp); // write data in new file
    
    remove(file); // remove current file
    
    fclose(fp);
    fclose(new_fp);
}

void do_rename(char *old_file, char *new_file){
    // the name of the file to be renamed. 
    if (rename(old_file, new_file) < 0){
        perror(old_file);
    }
}
