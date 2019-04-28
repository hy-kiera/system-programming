#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <limits.h>

#include "headers/execute.h"

#define MAX_LEN 100 // The maximum length command

void cd(int argc, char *args[]);
void history(int argc, char *args[], char *hist[]);
void hysh(int argc);

int main(void) {
    char *args[MAX_LEN / 2 + 1]; // command line arguments
    int should_run = 1;          // flag to determine when to exit program
    int background = 0;

    char *user_input; // user input cmd
    char *input;
    int status;
    int argc; // a number of arguments
    char *hist[500]; // record user cmds(by 500)
    int cnt = 0;

    char cwd[PATH_MAX]; // get current working path

    // simple introduction of hysh
    printf("\033[0;35m  _               _     \n | |__  _   _ ___| |__  \n | '_ \\| | | / __| '_ \\ \n | | | | |_| \\__ \\ | | |\n |_| |_|\\__, |___/_| |_|\n        |___/           \nVersion 1.0\033[0m\n\nType\"hysh\"! :D\n\n");


    while (should_run) {
        // get current working directory
        if(getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("\033[0;35m%s\033[0m \033[0;33m$\033[0m ", cwd);
        }
        fflush(stdout);

        user_input = (char*)malloc(MAX_LEN*sizeof(char));
        fgets(user_input, MAX_LEN, stdin); // get user command input and its arguments

        input = strdup(user_input); // duplicate user input
        
        cnt = cnt % 500;
        hist[cnt] = strtok(input, "\n"); // record cmd
        cnt++;

        int i = 0;
        args[i] = strtok(user_input, " \n"); // command
        
        while (args[i] != NULL) {
            i++;
            args[i] = strtok(NULL, " \n"); // arguments
        }
        argc = i;
        
        if (args[0] == NULL) // just enter
            goto no_input;

        // terminate hysh
        // if (strcmp(args[0], "exit") == 0) {
        //     exit(0);
        // }
    	
        background = 0;
        
        // activate background
        if (strcmp(args[i-1], "&") == 0) {
            args[i - 1] = NULL;
            background = 1;
        }
	
        // fork a process
        pid_t pid = fork();
        
        if (pid < 0) {
            perror("Fork error");
            exit(0);
        }

        if (pid == 0) {
            if (!strcmp(args[0], "cd")) cd(argc, args);
            else if (!strcmp(args[0], "history")) history(argc, args, hist);
            else if (!strcmp(args[0], "hysh")) hysh(argc);
            else execution(argc, args); // void execution(int argc, char *args[])
        }

        if (pid > 0) {
            if (!background) {
                waitpid(pid, NULL, 0);
            }
        }		
        
        no_input:
            continue;
    }
    
    free(input);
    return 0;
}

/* cd : change the current working directory */

void cd(int argc, char *args[]){
    char path[MAX_LEN];
    
    if (argc <= 2){
        if (argc == 1) strcpy(path, "/");
        else strcpy(path, args[1]);
        // makes pathname your new working directory
        if (chdir(path) != 0) fprintf(stderr, "cd: no such file or directory: %s\n", args[1]);
    }
    else{
        fprintf(stderr, "cd: string not in pwd: %s\n", args[1]);
    }
}

void history(int argc, char *args[], char *hist[]){
    int i;

    if (argc > 3) fprintf(stderr, "%s: too many arguments\n", args[0]);
    // no option
    else if (argc == 1){ // hist
        i = 0;
        while(hist[i] != NULL || i > 500){
            printf("%-6d%s\n", i, hist[i]);
            i++;
        }
    }
    // with option
    else{
        // argc == 3, macro of executing current <n> cmds
        if (!strcmp(args[1], "-mc")){
            // CODE HERE
        }
        // show help
        else if (!strcmp(args[1], "--help") || !strcmp(args[1], "-h")){
            printf("usage :\n");
        }
        // wrong option
        else{
            fprintf(stderr, "-hysh: %s: %s: invalid signal specification", args[0], args[1]);
        }
    }
}

void hysh(int argc){
    if (argc == 1){ // hysh
        printf("\033[0;35m  _               _     \n | |__  _   _ ___| |__  \n | '_ \\| | | / __| '_ \\ \n | | | | |_| \\__ \\ | | |\n |_| |_|\\__, |___/_| |_|\n        |___/           \033[0m\n");
        printf("CMDS\n");
        printf("ls : list files(directories) in the current path\n");
        printf("pwd : print the name of the current(working) directory\n");
        printf("cd : change the current working directory\n");
        printf("mkdir : make a directory\n");
        printf("rm : remove files or directories\n");
        printf("mv : moves one or more files or directories from one place to another\n");
        printf("cp : copy a file or a directory from one directory to another\n");
        printf("echo : output the strings it is being passed as arguments\n");
        printf("cat : concatenate and print files\n");
        printf("clear : bring the command line on top of the terminal\n");
        printf("hello : create a hello.c that prints 'hello world!'\n");
        printf("WITH OPTIONS\n\n");
        printf("\033[0;31mcp\033[0m [options] [source file] [target file] <new name>\n\n[options]\n\n-C : Move the directory where has the copied file, after coping source file.\n\n-m : copy a file renamed.\n\n--help, -h : Show help.\n\n");
        printf("\033[0;31mhello\033[0m [options] <path>\n\n[options]\n\n-p : create hello.c in a path that user input.\n\n-mf <path>: create hello.c with Makefile.\n\n--help, -h : Show help.\n\n");
        printf("\033[0;31mls\033[0m [options] [directory name ...]\n\n[options]\n\n-al, -all -la : List long format including hidden files.\n\n--help, -h : Show help.\n\n");
        printf("\033[0;31mmkdir\033[0m [options] [directory name ...]\n\n[options]\n\n-p : If the parent directories don't exist, this command creates them.\n\n-C : Make a directory and move to it.\n\n--help, -h : Show help.\n\n");
        printf("\033[0;31mmv\033[0m [options] <old_file>  <new_file>\n\n[options]\n\n-C : Move to the directory where a file is moved.\n\n--help, -h : Show help.\n\n");
        printf("\033[0;31mrm\033[0m [options] [files ...]\n\n-r : Attempt to remove the file hierarchy(directory) rooted in each file argument.\n\n-hd : Hide a file as if it were deleted.\n\n-u : Undo remove -hd\n\n--help, -h : Show help.\n\n");
    }
    else {
        fprintf(stderr, "hysh: too many arguments\n");
    }
}