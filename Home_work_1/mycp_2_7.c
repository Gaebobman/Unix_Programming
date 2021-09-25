#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFSIZE 512
#define FMODE O_WRONLY | O_CREAT | O_TRUNC 
#define PERM 0644
#define FILENAMESIZE 100

int copyfile(const char *name1, const char *name2){
    int infile, outfile;
    ssize_t nread;
    char buffer[BUFSIZE];

    if((infile = open (name1, O_RDONLY)) == -1)
        return (-1);

    if((outfile = open (name2, FMODE, PERM)) == -1){
        close(infile);
        return(-2);
    }

    while((nread = read(infile, buffer, BUFSIZE)) > 0){
        if( write (outfile, buffer, nread) < nread){
            close(infile);
            close(outfile);
            return(-3);
        }
    }

    close(infile);
    close(outfile);

    if(nread == -1) return(-4);
    else return (0);
}

int main(){
    char file1[FILENAMESIZE], file2[FILENAMESIZE];
    printf("Enter Name Of Original File: ");
    scanf("%s", file1);
    printf("Enter Name Of Destination File: ");
    scanf("%s", file2);
    switch (copyfile(file1, file2))
    {
    case -1:
        printf("There is no such Origianl file: %s !!!\n", file1);
        break;
    case -2:
        printf("There is no such Destination file: %s !!!\n", file2);
         break;
    case -3:
        printf("Error while writing file !!!\n");
         break;
    default:
        printf("COPY SUCCEED !!! \n");
        break;
    }
}