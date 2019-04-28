#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

#include "headers/execute.h"

#define MAX_LEN 100 // The maximum length command

void cd(int argc, char *args[]);
void history(int argc, char *args[], char *hist[]);

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

    while (should_run) {
        printf("$ ");
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
        if (strcmp(args[0], "exit") == 0) {
            exit(0);
        }
    	
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