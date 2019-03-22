#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[]){
	int status;
	mode_t old;

	if(argc<2){
		fprintf(stderr, "%s : no arguments\n", argv[0]);
		exit(1);
	}

	old = umask(0);
	for(int i=1; i<argc; i++){
		status = mkdir(argv[i], S_IRUSR | S_IWUSR | S_IXUSR \
								| S_IRGRP | S_IWGRP | S_IXGRP \
								| S_IROTH | S_IWOTH | S_IXOTH);
	}
	umask(old);
	return 0;
}
