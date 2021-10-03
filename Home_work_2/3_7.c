// gcc 3_7.c -o 3_7 -lm
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#define PERM_LENGTH 9
#define OCT_PERM_LENGTH 4

const char WEIGHT[] = {'4', '2', '1', '4', '2', '1', '4', '2', '1'};

mode_t lsoct(char *permission);

int main(int argc, char *argv[])
{
    int oct_permission[OCT_PERM_LENGTH] = {0};
    mode_t mode;
    if (access(argv[1], F_OK) == 0)
    {
        if (argv[2][0] == '0')
        { // if user gave octal permission argument
            // Change argv to octal value

            char S = argv[2][0] - '0';
            char USER_CHAR = argv[2][1] - '0';
            char GROUP_CHAR = argv[2][2] - '0';
            char OTHER_CHAR = argv[2][3] - '0';

            mode = OTHER_CHAR;
            mode |= GROUP_CHAR << 3;
            mode |= USER_CHAR << 6;
            mode |= S << 9;

            if (chmod(argv[1], mode) != -1)
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
            mode = lsoct(argv[2]);
            if (chmod(argv[1], mode) != -1)
            {
                printf("Permission changed: %s\n", argv[2]);
            }
            else
            {
                perror("Permissions have not changed: ");
            }
            
        }
    }
    else
    {
        printf("File (%s)does not exists\n", argv[1]);
    }
    return 0;
}

mode_t lsoct(char *permission)
{
    char oct_permission[OCT_PERM_LENGTH] = {'0'};
    for (int i = 0; i <= PERM_LENGTH; i++)
    {
        if (permission[i] != '-')
        {
            switch (i)
            {
            case 0:
            case 1:
            case 2:
                oct_permission[1] += WEIGHT[i] -'0';
                break;
            case 3:
            case 4:
            case 5:
                oct_permission[2] += WEIGHT[i]-'0';
                break;
            case 6:
            case 7:
            case 8:
                oct_permission[3] += WEIGHT[i]-'0';
                break;
            default:
                break;
            }
        }
    }
    mode_t mode;
    char S = oct_permission[3];
    char USER_CHAR = oct_permission[2];
    char GROUP_CHAR = oct_permission[1];
    char OTHER_CHAR = oct_permission[0];

    mode = OTHER_CHAR;
    mode |= GROUP_CHAR << 3;
    mode |= USER_CHAR << 6;
    mode |= S << 9;

    return mode;
}