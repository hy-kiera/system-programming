#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_LEN 100 /* The maximum length command */

int main(void) {
    char *args[MAX_LEN / 2 + 1]; /* command line arguments */
    int should_run = 1;          /* flag to determine when to exit program */
    int background = 0;

    char *input;
    int status;

    while (should_run) {
        printf("$ ");
        fflush(stdout);

        input = (char*)malloc(MAX_LEN*sizeof(char));
        fgets(input, MAX_LEN, stdin); // get user command input and its arguments

        int i = 0;
        args[i] = strtok(input, " \n"); // command
        
        while (args[i] != NULL) {
            i++;
            args[i] = strtok(NULL, " \n"); // arguments
            printf("args[%d] : %s\n", i, args[i]);
        }
        
        if (args[0] == NULL) // just enter
            goto no_input;

        // terminate hysh
        if (strcmp(args[0], "exit") == 0) {
            break;
        }
    	
        background = 0;
        
        // activate background
        if (strcmp(args[i-1], "&") == 0) {
            args[i - 1] = NULL;
            background = 1;
        }
		
        pid_t pid = fork();
        
        if (pid < 0) {
            perror("Fork error");
            exit(0);
        }

        if (pid == 0) {
            execvp(args[0], args);
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
