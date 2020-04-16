//
// Created by Zhicong Wen on 4/3/20.
//
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(){

    // Create Dir0
    char *filename = "Dir0";
    int status = mkdir(filename, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
//    if(!status){
//        printf("Error\n");
//    }
//    else{
//        printf("Directory created successful!\n");
//    }

    chdir(filename);
    int t1 = open("t1.txt", O_RDWR | O_CREAT , S_IRWXU | S_IRWXG | S_IRWXO );
    int t2 = open("t2.txt", O_RDWR | O_CREAT , S_IRWXU | S_IRWXG | S_IRWXO );
    int t3 = open("t3.txt", O_RDWR | O_CREAT , S_IRWXU | S_IRWXG | S_IRWXO );


    mkdir("Dir1", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    //chdir("Dir1");
    return 0;
}
