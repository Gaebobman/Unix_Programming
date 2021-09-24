#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFSIZE 1024

/* */

int count(char* arg[]){

    
}
int main(){
    int fd;
    // ssize_t ;
    char command[100];
    char buf[BUFSIZE];

    printf("Enter file name: ");
    scanf("%s", command);

    if((fd = open(command, O_RDONLY)) == -1){
        printf("open() Error!\n");
        exit(1);
    }else{
        
    }
    

    close(fd);
    return 0;
}