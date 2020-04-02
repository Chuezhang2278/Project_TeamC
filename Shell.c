// Sources taken by Chue

// https://indradhanush.github.io/blog/writing-a-unix-shell-part-2/
// https://github.com/Chuezhang2278/CSC332-OperatingSys/blob/master/task4_Chue_Zhang/Part1.c
// https://www.geeksforgeeks.org/making-linux-shell-c/

#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 
#include<readline/readline.h> 
#include<readline/history.h> 

#define clear() printf("\033[H\033[J") 

void cdout() // Is cd.. 
{
	char path[100];
	chdir("..");
	printf("%s\n", getcwd(path,100)); // print path
}

void cdin(char *arg) // Takes string arg to go to next dir , i.e OS folder... you do cd OS to go in
{
	char path[100];
	chdir(arg);
	printf("%s\n", getcwd(path,100)); // print path
}

void input(){ // How we take inputs in our shell, for more explanation go to ChueZhang OS332 Repo, task 5 part 1
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
		if(strcmp(arg[0], "cd") == 0) // Special case just for CD, unsure if any bugs since haven't tested fully
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
	do
	{
		input();
	}
	while(1);
	
} 



