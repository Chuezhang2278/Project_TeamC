// Shell sources

// https://indradhanush.github.io/blog/writing-a-unix-shell-part-2/
// https://github.com/Chuezhang2278/CSC332-OperatingSys/blob/master/task4_Chue_Zhang/Part1.c

#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 
#include<readline/readline.h> 
#include<readline/history.h> 

#define clear() printf("\033[H\033[J") 

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
	do
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

		pid1 = fork();   
		if(pid1 == 0)
		{	

			execvp(arg[0], arg);

		}
	}
	while(strcmp(n, "quit") !=0);      
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



