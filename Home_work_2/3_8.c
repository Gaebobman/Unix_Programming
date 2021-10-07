#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    char remove_confirmation_flag;
    if (argc != 2)
    {
        printf("argv error!!!");
        return -1;
    }

    if (access(argv[1], F_OK) == -1)
    {
        printf("There is no such file %s \n", argv[1]);
        return -1;
    }

    if (access(argv[1], W_OK == -1))
    {
        printf("You don't have WRITE PERMISSION");
        return -1;
    }
    else
    {
        printf("Remove file: %s? [y,N]: ", argv[1]);
        scanf("%c", &remove_confirmation_flag);
        if (remove_confirmation_flag == 'y' || remove_confirmation_flag == 'Y')
        {
            //if user hit YES, proceed unlink
            if (unlink(argv[1]) == -1)
            {
                perror("unlink failed\n");
                return -1;
            }
        }
        else if (remove_confirmation_flag == 'n' || remove_confirmation_flag == 'N')
        { //if user hit NO, abort
            printf("unlink canceled\n");
            return 0;
        }
        else
        {
            printf("Insert only y, Y, n, N \n");
        }
    }
    printf("unlink on %s succeeded", argv[1]);

    return 0;
}