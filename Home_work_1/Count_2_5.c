#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFSIZE 1024

/* 

' '      space 
'\t'     horizontal tab 
'\n'     newline
'\v'     vertical tab 
'\f'     form feed 
'\r'     carriage return    
*/

int main(){
    int fd;
    // ssize_t ;
    char command[100];
    char buf[BUFSIZE];
    int wordcount = 1;
    int linecount = 0;

    printf("Enter file name: ");
    // scanf("%s", command);

    if((fd = open("./newfile", O_RDONLY)) == -1){
        printf("open() Error!\n");
        exit(1);
    }else{
        read(fd,buf,BUFSIZE);
        for(int i = 0 ; i < sizeof(buf); i++){
            printf("%c", buf[i]);
            
            // Words are identified by spaces so...
            if(buf[i] == ' ' || buf[i] == '\t' || buf[i] == '\v' || buf[i] == '\f' || buf[i] == '\r'){
                wordcount++;
            }
            
            if(buf[i] == '\n'){
                linecount++;
            }

            //End Loop when buf[i] is EOF
            if(buf[i]<0 || buf[i]>127 ){
                break;
            }
        }
    }
    printf("Number of words: %d\nNumber of lines: %d", wordcount+1, linecount +1);
    close(fd);
    return 0;
}