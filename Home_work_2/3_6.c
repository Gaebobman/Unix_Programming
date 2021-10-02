#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#define MAX_FILENAME_LENGTH 256

void whatever(char *file_name)
{
    bool flag = false;
    if (access(file_name, F_OK) == 0)
    { // Check if file exists
        // Check READ
        if (access(file_name, R_OK) == 0)
        {
            printf("You can READ this file\n");
            flag = true;
        }
        else
        {
            perror("You can't READ this file");
        }
        // Check WRITE
        if (access(file_name, W_OK) == 0)
        {
            printf("You can WRITE this file\n");
            flag = true;
        }
        else
        {
            perror("You can't WRITE this file");
        }
        // Check EXECUTE
        if (access(file_name, X_OK) == 0)
        {
            printf("You can EXECUTE this file\n");
            flag = true;
        }
        else
        {
            perror("You can't EXECUTE this file");
        }
        // Check if file has no permission
        if (flag == false)
        {
            printf("File exists but there is no single permission\n");
        }
    }
    else
    { // There is no such file
        printf("File (%s)does not exists !!!\n", file_name);
    }
}

int main()
{
    char file_name[MAX_FILENAME_LENGTH];

    printf("Enter Filename: ");
    scanf("%s", file_name);
    whatever(file_name);
    return 0;
}