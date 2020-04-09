// Jia  Ming Ma

#include <unistd.h>
#include <stdio.h>
#include <dirent.h> 
#include <sys/types.h>
#include <pwd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <grp.h>

int main(){

    struct dirent *de;  // Pointer for reading
    DIR *dr = opendir("."); // Pointer of directory
  
    if (dr == NULL) { 
        printf("Could not open current directory" ); 
        return 0; 
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
    return 0; 
}