/* rm : remove files or directories */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>

#include "../headers/cmds.h"
#include "../headers/utils.h"

void rm(int argc, char *args[]);
void rm_path(const char *path);
void file_hide(char *file);
void undo_hide(char *file);


void rm(int argc, char *args[]){
    int i;
    int stMode;

    if (argc < 2) fprintf(stderr, "%s : no arguments\n", args[0]);

    if (argc >= 2){
        // no option
        if (args[1][0] != 45){ // "-" : 45(ascii code
            stMode = get_type(args[1]);
            // check args is a directory or not
            if (S_ISDIR(stMode)) fprintf(stderr, "rm: %s: is a directory", args[1]);
            else {
                for(i = 1; i < argc; i++){
                    if (remove(args[i]) == -1) fprintf(stderr, "rm: %s: no such file or a directory\n", args[i]);
                }
            }
        }
        // with option
        else {
            stMode = get_type(args[2]);

            // remove the file hierarchy
            if (!strcmp(args[1], "-r")){
                printf("DEVELOPING\n");
                // for(i = 2; i < argc; i++){
                //     rm_path(args[i]);
                // }
            }
            // not remove but hide(look being removed)
            else if (!strcmp(args[1], "-hd")){
                if (S_ISDIR(stMode)) fprintf(stderr, "rm: %s: is a directory", args[2]);
                else{
                    for(i = 2; i < argc; i++){
                        file_hide(args[i]);
                    }
                }
            }
            // undo hidden(look being removed) file
            else if (!strcmp(args[1], "-u")){
                if (S_ISDIR(stMode)) fprintf(stderr, "rm: %s: is a directory", args[2]);
                // "." : 46(ascii code)
                if (args[2][0] != 46) fprintf(stderr, "rm: %s: is not a hidden file\n", args[2]);
                if(!S_ISDIR(stMode) && args[2][0] == 46){
                    for(i = 2; i < argc; i++){
                        undo_hide(args[i]);
                    }
                }
            }
            // show help
            else if (!strcmp(args[1], "--help") || !strcmp(args[1], "-h")){
                printf("usage : rm [options] [files ...]\n\nremove files or directories\n\n[options]\n\n-r : Attempt to remove the file hierarchy(directory) rooted in each file argument.\n\n-ri : Remove the file hierarchy and the user has been prompted for confirmation before each directory's contents are processed (as well as before the attempt is made to remove the directory).\n\n-hd : Hide a file as if it were deleted.\n\n-u : Undo remove -hd\n\n--help, -h : Show help.\n");
            }
            else {
                fprintf(stderr, "-hysh: %s: %s: invalid signal specification\n", args[0], args[1]);
            }
        }
    }
}

void rm_path(const char *path){
    DIR *dp;
    struct dirent * ent;
    int stMode;
    char buf[255], pathName[255];
   
    // opens a directory so that it can be read
    if ((dp = opendir(path)) == NULL) fprintf(stderr, "rm: %s: No surch file or directory\n", path);
    
    // returns a pointer to a dirent structure describing the next directory entry in the directory stream associated with dp
    while((ent = readdir(dp)) != NULL){
        if (ent->d_ino != 0){ // inode number of the file
            stMode = get_type(ent->d_name); // get type of the filename
            sprintf(buf, "%s/%s", path, ent->d_name); // get path of the sub directory
            // dir entry is a directory
            if (S_ISDIR(stMode)){
                printf("dir->d_name : %s\n", ent->d_name);
                if (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0){
                    // chdir(buf);
                    rm_path(buf);
                }
            }
            // dir entry is a file
            else{
                printf("remove file\n");
                remove(ent->d_name);
            }
        }
    }
    // chdir("../");
    closedir(dp);
}

// hide file
void file_hide(char *file){
    char new_file[256];

    strcpy(new_file, ".");
    strcat(new_file, file); // .<file>

    // the name of the file to be renamed. 
    if (rename(file, new_file) < 0) perror(file);
}

// reveal hidden file
void undo_hide(char *file){
    char *new_file;

    new_file = file + 1;
    // the name of the file to be renamed. 
    if (rename(file, new_file) < 0) perror(file);
}