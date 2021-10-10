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
    mode_t oct_permission = 0b0;

    for (int i = 0; i <= PERM_LENGTH; i++)
    {
        if (permission[i] != '-')
        {
            switch (i)
            {
            case 0:
                oct_permission |= 0b100000000;
                break;
            case 1:
                oct_permission |= 0b010000000;
                break;
            case 2:
                oct_permission |= 0b001000000;
                break;
            case 3:
                oct_permission |= 0b000100000;
                break;
            case 4:
                oct_permission |= 0b000010000;
                break;
            case 5:
                oct_permission |= 0b000001000;
                break;
            case 6:
                oct_permission |= 0b000000100;
                break;
            case 7:
                oct_permission |= 0b000000010;
                break;
            case 8:
                oct_permission |= 0b000000001;
                break;
            default:
                break;
            }
        }
    }
    return oct_permission;
}