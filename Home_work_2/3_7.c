// gcc 3_7.c -o 3_7 -lm
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define PERM_LENGTH 9
#define OCT_PERM_LENGTH 4

const int WEIGHT[] = {4, 2, 1, 4, 2, 1, 4, 2, 1};

void lsoct(char *permission,  int *oct_permission);

int main(int argc, char *argv[])
{
    int oct_permission[OCT_PERM_LENGTH] = {0};
    int integer_oct_permission = 0;
   
   printf("%d\n", atoi(argv[2]));
    if (access(argv[1], F_OK) == 0)
    {
        if (sizeof(argv[2]) == 8)
        { // if user gave octal permission argument
            if (chmod(argv[1], atoi(argv[2])) != -1)
            {
                printf("Permissions have changed: %s\n", argv[2]);
            }
            else
            {
                perror("Permissions have not changed: ");
            }
        }
        else
        { // if user gave ls permission argument
            for(int i = 0 ; i < 2; i++){
                integer_oct_permission += oct_permission[i] * pow(10.0, (double)(2-i));
            }
            if (chmod(argv[1], integer_oct_permission) != -1)
            {
                printf("Permission changed: %d\n", integer_oct_permission);

            }
            else
            {
                perror("Permissions have not changed: ");
            }
        }
    }
    else
    {
        printf("File (%s)does not exists", argv[1]);
    }
    return 0;
}

void lsoct(char *permission, int *oct_permission)
{
    for (int i = 0; i <= PERM_LENGTH; i++)
    {
        if (permission[i] != '-')
        {
            switch (i)
            {
            case 0:
            case 1:
            case 2:
                oct_permission[1] += WEIGHT[i];
                break;
            case 3:
            case 4:
            case 5:
                oct_permission[2] += WEIGHT[i];
                break;
            case 6:
            case 7:
            case 8:
                oct_permission[3] += WEIGHT[i];
                break;
            default:
                break;
            }
        }
    }
    for (int i = 0; i < OCT_PERM_LENGTH; i++)
    {
        printf("%d", oct_permission[i]);
    }

}