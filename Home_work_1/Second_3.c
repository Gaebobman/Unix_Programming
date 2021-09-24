#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(){
    int fd;
    // Owner has permission on RW  / Group and others only have Read
    fd = creat("./newfile", 0644);
        if(fd > 0){
            printf("creat() Succeed!\n");
            if(open("./newfile", O_RDWR) > 0){
                printf("open() Succeed!\n");
            }else{
                printf("open() Failed!\n");
            }
        }else{
            printf("creat() Failed\n");
        }
        if(close(fd) == 0){
            printf("close() Succeed!\n");
        }else{
             printf("close() Failed\n");
        }
    return 0;
}   