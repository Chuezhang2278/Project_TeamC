// CSc 332 - Group Project: exit
// By Eric Mai (Section T)

/* Resources used:
   https://www.geeksforgeeks.org/print-last-10-lines-of-a-given-file/ */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h> 
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <string.h> 

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

/* Using the same method for "ls -l" as done by Jia Ming Ma in the list.c file */
void printDetailedList() {
    printf("List of all content in the current directory...\n");

    struct dirent *de;  // Pointer for reading
    DIR *dr = opendir("."); // Pointer of directory
  
    if (dr == NULL) { 
        printf("Could not open current directory" ); 
        return; 
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

            printf("%d\t", fileInfo.st_size); // using stats, we can find the bytes of each file

            char date[20];
            strftime(date, 20, "%b %d %H:%M", localtime(&(fileInfo.st_ctime))); // converting the time from stats into a char for display
            printf("%s\t", date);
        }
        printf("%s\n", de->d_name); 
    }
    closedir(dr);
    free(de);
}

/* Method terminates shell after "return" key is pressed */
void returnTerminate() {
    printf("\nHit the \"return\" key to terminate...");
    while(getchar() != '\n')
        ; // empty loop
    exit(0);
}

int main() {
    int numCommands = 0;
    printf("Enter number of commands: ");
    scanf("%d", &numCommands);

    char command[100];
    char history[8192];
    /* For some reason fgets causes the loop to skip ahead by 1 */
    while(numCommands > 0) {
        fgets(command, 100, stdin); 
        strcat(history, command);
        numCommands--;
    }

    printf("------------------------\n");
    printLastFourCommands(history);
    printDetailedList();
    returnTerminate();

    return 0;
}