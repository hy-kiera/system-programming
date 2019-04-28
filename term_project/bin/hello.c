/* create a hello.c that prints 'hello world!' */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/cmds.h"

void create_file(char path[], char *words, char *filename);

void hello(int argc, char *args[]){
    char *hello = "#include <stdio.h>\n\nint main(int argc, char *argv[]){\n    printf(\"hell    o world\");\n    return 0;\n}";
    char *makefile = "hello: hello.c\n\tgcc -o hello hello.c\n\nclean: rm hello";
    char *hello_c_name = "/hello.c";
    char *makefile_name = "/Makefile";


    if (argc > 3) fprintf(stderr, "%s: too many arguments\n", args[0]);
    // no option
    else if (argc == 1){ // hello
        create_file(".", hello, hello_c_name);
    }
    // with option
    else{
        // create hello.c in specific path
        if (!strcmp(args[1], "-p")){
            create_file(args[2], hello, hello_c_name);
        }
        // create hello.c with Makefile in specific path
        else if (argc == 3 && !strcmp(args[1], "-mf")){
            create_file(args[2], hello, hello_c_name);
            create_file(args[2], makefile, makefile_name);
        }
        // create hello.c with Makefile
        else if (argc == 2 && !strcmp(args[1], "-mf")){
            create_file(".", hello, hello_c_name);
            create_file(".", makefile, makefile_name);
        }
        // show help
        else if (!strcmp(args[1], "--help") || !strcmp(args[1], "-h")){
            printf("usage : hello [options] <path>\n\ncreate a hello.c that prints 'hello world!'\n\n[options]\n\n-p : create hello.c in a path that user input.\n\n-mf <path>: create hello.c with Makefile.\n\n--help, -h : Show help.\n");
        }
        // wrong option
        else{
            fprintf(stderr, "-hysh: %s: %s: invalid signal specification", args[0], args[1]);
        }
    }
}

void create_file(char *path, char *words, char *filename){
    FILE *fp;
    char file[256];

    // make path
    strcpy(file, path);
    strcat(file, filename);

    fp = fopen(file, "w+"); // open hello.c file
    if(fp == NULL) fprintf(stderr, "hello: no such directory\n");
    fputs(words, fp); // write words in fp
    
    fclose(fp);
}
