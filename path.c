// Garland Qiu
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>


int main() {
	char cwd[PATH_MAX];

	// gets current directory path
	if(getcwd(cwd, sizeof(cwd)) != NULL) {
		printf("Current Working Directory: %s\n", cwd);
	}
	else {
		perror("getcwd() error");
		// return 1;
	}

	// gets t2.txt directory path
	// check if Dir0 exists
	if(chdir("/Dir0") != 0) {
		perror("Directory Dir0 does not exist");
	}
	// try to access t2.txt
	else {
		int fd = access("t2.txt", F_OK);
		if(fd == -1) {
			printf("Error %d\n", errno);
			perror("Error:");
		}

		else {
			char t2_cwd[PATH_MAX];
			if(getcwd(t2_cwd, sizeof(t2_cwd)) != NULL) {
				printf("t2.txt Working Directory: %s\n", t2_cwd);
			}
			else {
				perror("getcwd() error");
				// return 1;
			}

			// Changing name of t2.txt to path-info.txt
			char t2_txt[] = "t2.txt";
			char path_info_txt[] = "path-info.txt";
			int ret = rename(t2_txt, path_info_txt);
			if(ret == 0) {
				printf("t2.txt renamed to path-info.txt");
			}
			else {
				printf("Unable to rename file");
			}
		}
	}

	// concatenating contents of tree.txt and path-info.txt
	FILE *tree_file = fopen("tree.txt", "r");
	FILE *path_file = fopen("path-info.txt", "r");
	FILE *t3_file = fopen("t3.txt", "w");

	// check if files can read and write
	if(tree_file == NULL || path_file == NULL || t3_file == NULL) {
		printf("Cannot open files");
		exit(0);
	}

	char c;
	// copy contents of tree.txt to t3.txt
	while((c = fgetc(tree_file)) != EOF) {
		fputc(c, t3_file);
	}

	// copy contents of path-info.txt to t3.txt
	while((c = fgetc(path_file)) != EOF) {
		fputc(c, t3_file);
	}

	fclose(tree_file);
	fclose(path_file);
	fclose(t3_file);
	printf("Merged tree.txt and path-info.txt to t3.txt");

	// rename t3.txt to log.txt
	char t3_txt[] = "t3.txt";
	char log_txt[] = "log.txt";
	int ret = rename(t3_txt, log_txt);
	if(ret == 0) {
		printf("t3.txt renamed to log.txt");
	}
	else {
		printf("Unable to rename file");
	}

	// delete tree and path text files
	if(remove("tree.txt") == 0) {
		printf("tree.txt deleted successfully");
	}
	else {
		printf("unable to delete tree.txt");
	}

	if(remove("path-info.txt") == 0) {
		printf("path-info.txt deleted successfully");
	}
	else {
		printf("unable to delete path-info.txt");
	}

	return 0;
}