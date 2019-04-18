#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

// handler function
void handler(int signo){
	printf("Signal Handler Signal Number : %d\n", signo);
	psignal(signo, "Received Signal");
}

int main(void) {
    void (*hand)(int);

    // set handler
	hand = signal(SIGINT, handler);

	// handler error
	if (hand == SIG_ERR) {
   	    perror("signal");
        exit(1);
    }

	// wait for the interrupt from pause function
	pause();
    return 0;
}
