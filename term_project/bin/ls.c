/* ls : list files(directories) in a path */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>
#include <string.h>

#include "../headers/cmds.h"
#include "../headers/utils.h"

static void do_ls(char *path, int btn);
static void do_ls_al(char *path);

void ls(int argc, char *args[]){
    int i;

    // list files in the working directory
    if (argc == 1){
        do_ls("./", 0);
    }
    
    if (argc >= 2){
        // no option
        if (args[1][0] != 45){ // "-" : 45(ascii code)
            if (argc > 2){ // multiple arguments(path)
                for(i = 1; i < argc; i++){
                    printf("%s:\n", args[i]);
                    do_ls(args[i], 0);
                }
            }
            else{ // single argument(path)
                do_ls(args[1], 0);
            }
        }
        // with option
        else{
            // list all files
            if (!strcmp(args[1], "-a")){
				if (argc > 3){ // multiple argutments(path)
                    for(i = 1; i < argc; i++){
                        printf("%s:\n", args[i]);
                        do_ls(args[i], 1);
                    }
                }
                else if (argc == 3){ // single argument(path)
                    do_ls(args[2], 1);
                }
				else{ // no argument(path)
					do_ls("./", 1);
				}
            }
            // list all files with their information(permission, owner, file size, date)
            else if (!strcmp(args[1], "-al") || !strcmp(args[1], "-all") || !strcmp(args[1], "-la")){
                if (argc > 3){ // multiple argutments(path)
                    for(i = 1; i < argc; i++){
                        printf("%s:\n", args[i]);
                        do_ls_al(args[i]);
                    }
                }
                else if (argc == 3){ // single argument(path)
                    do_ls_al(args[2]);
                }
				else{ // no argument(path)
					do_ls_al("./");
				}
            }
            // show help
            else if (!strcmp(args[1], "-h") || !strcmp(args[1], "--help")){
                printf("usage : ls [options] [directory name ...]\n\nlist files in a working directory.\n\n[options]\n\n-al, -all -la : List long format including hidden files.\n\n--help, -h : Show help.\n");
            }
            // wrong option
            else{
                fprintf(stderr, "-hysh: %s: %s: invalid signal specification", args[0], args[1]);
			}
        }
    }
}

static void do_ls(char* path, int btn){
    DIR *dp; // directory pointer
    struct dirent *ent; // entries in directory
	struct stat st; // state

	// opens a directory so that it can be read
    dp = opendir(path);
    if ((dp = opendir(path)) == NULL) fprintf(stderr, "ls: %s: No surch file or directory\n", path);

	// returns a pointer to a dirent structure describing the next directory entry in the directory stream associated with dp
    while(ent = readdir(dp)){
		if (btn){
			printf("%s\nd", ent->d_name);
		}
		else{
			// "." : 46(ascii code
			if (ent->d_name[0] != 46) printf("%s\n", ent->d_name);
		}
    }
    closedir(dp);
}

static void do_ls_al(char *path){   
    DIR *dp;
	struct dirent *ent;
	char buf[2048]; // buf for path
	struct stat st; // state
	char *mtime; // modified time
	char msg[50];
	
	// opens a directory so that it can be read
	dp = opendir(path);
	if ((dp = opendir(path)) == NULL) fprintf(stderr, "ls: %s: No surch file or directory\n", path);

	// returns a pointer to a dirent structure describing the next directory entry in the directory stream associated with dp
    while ((ent = readdir(dp))) {
        sprintf(buf, "%s/%s", path, ent->d_name);
        		
        if (lstat(buf, &st) < 0) perror(buf);
        mtime = ctime(&st.st_mtime); // get modification time of files
        mtime[strlen(mtime) - 1] = '\0'; // ctime returns a string terminated by '\n', remove it
        
        // get permission
        printf((S_ISDIR(st.st_mode)) ? "d" : "-");
        printf((st.st_mode & S_IRUSR) ? "r" : "-");
        printf((st.st_mode & S_IWUSR) ? "w" : "-");
        printf((st.st_mode & S_IXUSR) ? "x" : "-");
        printf((st.st_mode & S_IRGRP) ? "r" : "-");
        printf((st.st_mode & S_IWGRP) ? "w" : "-");
        printf((st.st_mode & S_IXGRP) ? "x" : "-");
        printf((st.st_mode & S_IROTH) ? "r" : "-");
        printf((st.st_mode & S_IWOTH) ? "w" : "-");
        printf((st.st_mode & S_IXOTH) ? "x" : "-");

		sprintf(msg, "%-4d%-6d %s %s", st.st_nlink, st.st_size, mtime, ent->d_name);
		printf("%s\n", msg);
    }
    closedir(dp);
}