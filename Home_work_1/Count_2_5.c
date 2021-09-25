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
    int wordcount = 0;
    int linecount = 0;
    int spacecount = 0;

    printf("Enter file name: ");
    scanf("%s", command);

    if((fd = open(command, O_RDONLY)) == -1){
        printf("open() Error!\n");
        exit(1);
    }else{
        read(fd,buf,BUFSIZE);
        for(int i = 0 ; i < sizeof(buf); i++){
            // printf("%c", buf[i]);
            
            // Words are identified by spaces so...
            if(buf[i] == ' ' || buf[i] == '\t' || buf[i] == '\v' || buf[i] == '\f' || buf[i] == '\r'){
                spacecount++;
            }
            
            if(buf[i] == '\n'){
                linecount++;
            }

            if(buf[i]<0 || buf[i]>127 ){
                break;
            }
        }
    }
    if(sizeof(buf) == linecount){
        wordcount = 0;
        linecount = 0;
    }else{
        wordcount = spacecount +1;
        linecount++;
    }
    
    printf("Number of words: %d\nNumber of lines: %d\n", wordcount, linecount);
    close(fd);
    return 0;
}