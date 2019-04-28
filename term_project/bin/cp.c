/* cp : copy a file or a directory from one directory to another */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#include "../headers/cmds.h"
#include "../headers/utils.h"

void do_copy(char *source_file, char *target_file, char *new_name);

void cp(int argc, char *args[]){
    int stMode;
    int is_dir;

    if (argc != 3 && argc != 4){
        fprintf(stderr, "%s: wrong arguments\n", args[0]);
    }

    // no option
    if (argc == 3){
        stMode = get_type(args[2]);
        is_dir = S_ISDIR(stMode); // returns non-zero if the file is a directory
        if(is_dir) do_copy(args[1], args[2], NULL);
    }

    stMode = get_type(args[3]);
    is_dir = S_ISDIR(stMode);
    // with option
    if (argc == 4 && is_dir){
        // move the directory where has the copied file, after coping source file.
        if (!strcmp(args[1], "-C")){
            do_copy(args[2], args[3], NULL);
            if (chdir(args[3]) != 0) fprintf(stderr, "cd: %s: no such file or directory\n", args[3]);
        }
        // copy a file renamed
        else if (!strcmp(args[1], "-m")){
            do_copy(args[2], args[3], args[4]); 
        }
        // show help
        else if (!strcmp(args[1], "--help") || !strcmp(args[1], "-h")){
            printf("usage : cp [options] [source file] [target file] <new name>\n\ncopy a file or a directory from one directory to another\n\n[options]\n\n-C : Move the directory where has the copied file, after coping source file.\n\n-m : copy a file renamed.\n\n--help, -h : Show help.\n");
        }
        else{
            // wrong option
            fprintf(stderr, "-hysh: %s: %s: invalid signal specification", args[0], args[1]);
        }
    }
}

void do_copy(char *source_file, char *target_file, char *new_name){
    FILE *s_fp, *t_fp;
    char new_path[256];
    char buffer[file_size(source_file)];

    strcpy(new_path, target_file);
    strcat(new_path, "/");
    if(new_name != NULL) strcat(new_path, new_name); 
    else strcat(new_path, source_file);

    s_fp = fopen(source_file, "r"); // open the source file for reading
    t_fp = fopen(new_path, "w+"); // create a target file

    fread(buffer, file_size(source_file) + 1, 1, s_fp); // read data from file
    fwrite(buffer, 1, sizeof(s_fp), t_fp); // copy data in target file
    
    fclose(s_fp);
    fclose(t_fp);
}
