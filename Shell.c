#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 
#include<sys/stat.h>
#include<readline/readline.h> 
#include<readline/history.h> 
#include<fcntl.h>
#include<grp.h>
#include<dirent.h>
#include<pwd.h>

#define clear() printf("\033[H\033[J") 

//==== Part done by ZhiCong Wen ====//
void tree() 
{
    char *filename = "Dir0";
    int status = mkdir(filename, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

    chdir(filename);
    int t1 = open("t1.txt", O_RDWR | O_CREAT , S_IRWXU | S_IRWXG | S_IRWXO );
    int t2 = open("t2.txt", O_RDWR | O_CREAT , S_IRWXU | S_IRWXG | S_IRWXO );
    int t3 = open("t3.txt", O_RDWR | O_CREAT , S_IRWXU | S_IRWXG | S_IRWXO );


    mkdir("Dir1", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    //chdir("Dir1");
}

//==== Part done by ZhiCong Wen ====//

///==== Part done by Jia Ming Ma ====///

void list()
{
    struct dirent *de;  // Pointer for reading
    DIR *dr = opendir("."); // Pointer of directory
  
    if (dr == NULL) { 
        printf("Could not open current directory" ); 
    } 
  
    while ((de = readdir(dr)) != NULL) { // reading directory while there is something
        struct stat fileInfo;
        if (stat(de->d_name, &fileInfo) == 0) {
            printf( (S_ISDIR(fileInfo.st_mode)) ? "d" : "-");// works because on success, fileInfo.st_mode returns 1, otherwise -1
            printf( (fileInfo.st_mode & S_IRUSR) ? "r" : "-");
            printf( (fileInfo.st_mode & S_IWUSR) ? "w" : "-");
            printf( (fileInfo.st_mode & S_IXUSR) ? "x" : "-");
            printf( (fileInfo.st_mode & S_IRGRP) ? "r" : "-");
            printf( (fileInfo.st_mode & S_IWGRP) ? "w" : "-");
            printf( (fileInfo.st_mode & S_IXGRP) ? "x" : "-");
            printf( (fileInfo.st_mode & S_IROTH) ? "r" : "-");
            printf( (fileInfo.st_mode & S_IWOTH) ? "w" : "-");
            printf( (fileInfo.st_mode & S_IXOTH) ? "x " : "- ");

            printf("%d\t", fileInfo.st_nlink); // using stats, we can access the number of links of each file

            struct passwd *pws;
            struct group *grpid;
            pws = getpwuid(fileInfo.st_uid); // get file pwuid with userid and then we can look at the user name
            grpid = getgrgid(fileInfo.st_uid); // get file groupid with userid and then we can look at group name
            printf("%s\t", pws->pw_name);
            printf("%s\t", grpid->gr_name);

            //printf("%d\t", fileInfo.st_size); // using stats, we can find the bytes of each file
		// Note from Chue: This doesn't seem to work as the there is an error with format typing, will figure out later

            char date[20];
            strftime(date, 20, "%b %d %H:%M", localtime(&(fileInfo.st_ctime))); // converting the time from stats into a char for display
            printf("%s\t", date);
        }
        printf("%s\n", de->d_name); 
    }
    closedir(dr);
    free(de);
}

///==== Part done by Jia Ming Ma ====///

////==== Part done by Eric Mai ====////

/* Method outputs the last 4 commands used in the shell */
void printLastFourCommands(char *str) {   
    printf("The last 4 commands used were...\n");

    size_t cnt  = 0; // To store count of '\n'
    char *target_pos   = NULL; // To store the output position in str 
  
    /* Step 1: Find the last occurrence of '\n' */
    target_pos = strrchr(str, '\n'); 
  
    /* Error if '\n' is not present at all */
    if (target_pos == NULL) 
    { 
        fprintf(stderr, "ERROR: string doesn't contain '\\n' character\n"); 
        return; 
    } 
  
    /* Step 2: Find the target position from where we need to print the string */
    while (cnt < 5) 
    { 
        // Step 2.a: Find the next instance of '\n' 
        while (str < target_pos && *target_pos != '\n') 
            --target_pos; 
         /* Step 2.b: skip '\n' and increment count of '\n' */
        if (*target_pos ==  '\n') 
            --target_pos, ++cnt; 
        /* str < target_pos means str has less than 5 '\n' characters, 
           so break from loop */
        else
            break; 
    } 
  
    /* In while loop, target_pos is decremented 2 times, that's why target_pos + 2 */
    if (str < target_pos) 
        target_pos += 2; 
  
    // Step 3: Print the string from target_pos 
    printf("%s\n", target_pos); 
} 

void returnTerminate() 
{
    printf("\nHit the \"return\" key to terminate...");
    while(getchar() != '\n')
        ; // empty loop
    exit(0);
}

////==== Part done by Eric Mai ====////

/////===== Part to be done by Garland Qiu =====/////
void path() {
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
/////===== Part to be done by Garland Qiu =====/////

//////===== Part done by Chue Zhang =====///////
void init_shell()
{
	printf("Initializing Team C's Terminal\n");
	printf("Initialized, please use commands list, exit, tree\n");
}

void cdout()
{
	char path[100];
	chdir("..");
	printf("%s\n", getcwd(path,100));
}

void cdin(char *arg)
{
	char path[100];
	chdir(arg);
	printf("%s\n", getcwd(path,100));
}

char history[8192];

void input(){ //combining all functions into the shell file
	char n[100];
	char N;
	int pid1;
	while(1){
		printf("->"); 
		char* arg[100];		
		char path[100];    			   
		fgets(n, 100, stdin);
		strcat(history, n);
		char *s = strchr(n, '\n');
		if(s){			   
			*s = '\0';
		}	   
		arg[0] = strtok(n," "); 
		int i = 0;		   
		while(arg[i] != NULL)      
		{			   
					  
			arg[++i] = strtok(NULL, " "); 
		}
		if(arg[0] == NULL)
			exit(0);
		if(strcmp(arg[0], "cd") == 0)
		{
			if(arg[1] != NULL)
			{
				printf("Going to directory specificed");
				cdin(arg[1]);
			}
			else
			{
				printf("Going to previous directory");
				cdout();
			}
		}

		if(strcmp(arg[0], "tree") == 0)
		{
			printf("Creating dir0 and contents\n");
			tree();
		}	
		if(strcmp(arg[0], "list") == 0)
		{
			clear();
			list();
			int ret;
			printf("Renaming t1.txt to tree.txt\n");
			ret = rename("t1.txt", "tree.txt");
		}

		if(strcmp(arg[0], "exit") == 0)
		{
			list();
			printLastFourCommands(history);
			printf("Press the ENTER key to exit\n"); 
			exit(0);
		}  
		pid1 = fork();
		if(pid1 == -1)
			printf("error forking");
		else if(pid1 == 0)	
			execvp(arg[0], arg);
		else
			wait(NULL);
		
	} 
	wait(NULL);
}

//////===== Part done by Chue Zhang =====//////

int main() 
{ 
    clear();
    init_shell(); 
	while(1)
		input();
} 
