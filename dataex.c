#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int fd;
    pid_t pid;
    caddr_t addr;
    struct stat statbuf;

    if (argc != 2) {
        fprintf(stderr, "Usage : %s filename\n", argv[0]);
        exit(1);
    }

    if (stat(argv[1], &statbuf) == -1) {
        perror("stat");
        exit(1);
    }

    if ((fd = open(argv[1], O_RDWR)) == -1) {
        perror("open");
        exit(1);
    }

	// memory mapping using mmap
	addr = mmap(NULL, statbuf.st_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, (off_t)0);
	if(addr == MAP_FAILED){
		perror("map");
		exit(1);
	}

    close(fd);

    switch (pid = fork()) {
        case -1 :  /* fork failed */
            perror("fork");
            exit(1);
            break;
        case 0 :   /* child process */
            // check data by printf
			printf("child : %s\n", addr);
            // change data and sync
			addr[0] = "H";
			msync(addr, statbuf.st_size, MS_SYNC);
			// check changed data
			printf("changed data(child) : %s\n", addr);
			break;
        default :   /* parent process */
            // check data by printf
			printf("parent : %s\n", addr);
			// change data and sync
			msync(addr, statbuf.st_size, MS_SYNC);
			// check changed data
			printf("changed data(parent) : %s\n", addr);
			break;
    }
	
	// munmap
	if(munmap(addr, statbuf.st_size) == -1){
		perror("munmap");
		exit(1);
	}
    return 0;
}
