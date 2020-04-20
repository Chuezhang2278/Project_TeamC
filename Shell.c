// Shell sources

// https://indradhanush.github.io/blog/writing-a-unix-shell-part-2/
// https://github.com/Chuezhang2278/CSC332-OperatingSys/blob/master/task4_Chue_Zhang/Part1.c

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
    if(!status){
        printf("Error\n");
    }
    else{
        printf("Directory created successful!\n");
    }

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

void printLastFourCommands() {
    printf("Last 4 commands used...\n");
    
}
/* Method terminates shell after "return" key is pressed */
void returnTerminate() {
    printf("\nHit the \"return\" key to terminate...");
    while(getchar() != '\n')
        ; // empty loop
    exit(0);
}

////==== Part done by Eric Mai ====////

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

void input(){
	char n[100];
	while(getchar() != '\n')
	{	
		char* arg[100];		
		char path[100];    	
		int pid1;
		//printf("~☞ "); 		   
		fgets(n, 100, stdin);
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
		if(strcmp(arg[0], "cd") == 0)
		{
			if(arg[1] != NULL)
				cdin(arg[1]);
			else
				cdout();
		}

		if(strcmp(arg[0], "tree") == 0)
		{
			tree();
		}
		
		if(strcmp(arg[0], "list") == 0)
		{
			list();
		}
		

		pid1 = fork();   
		if(pid1 == 0)
		{	

			execvp(arg[0], arg);

		}
	} 
	printLastFourCommands();   
	list(); 
	wait(NULL);
}

int main() 
{ 
    //init_shell(); 
	int n = 0;
	do
	{
		input();
	}
	while(n = 0);
	
} 


