#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

char *USAGE = "USAGE: <filename> <OCTAL_PERMISSION>";
int main(int argc, char *argv[])
{
    mode_t mode;
    struct stat stat_buffer;
    if (argc != 3)
    {
        printf("%s\n", USAGE);
        return -1;
    }
    //check if file exists
    if (access(argv[1], F_OK) == 0)
    { //if file exists, Check READ PERMISSION on file
        if (access(argv[1], R_OK) == -1)
        {
            printf("You don't have READ PERMISSION on %s", argv[1]);
            return -1;
        }
        //if file exists, Check WRITE PERMISSION on file
        if (access(argv[1], W_OK) == -1)
        {
            printf("You don't have WRITE PERMISSION on %s", argv[1]);
            return -1;
        }
        if (argv[2][0] != '0')
        {
            printf("Format error on argv[2]: 0xxx is correct format\n");
            return -1;
        }
        else
        {
            //convert arg[2] to mode_t, char* => mode_t(unsigned int)
            char S = argv[2][0] - '0';
            char USER_CHAR = argv[2][1] - '0';
            char GROUP_CHAR = argv[2][2] - '0';
            char OTHER_CHAR = argv[2][3] - '0';

            mode = OTHER_CHAR;
            mode |= GROUP_CHAR << 3;
            mode |= USER_CHAR << 6;
            mode |= S << 9;
        }
        //store file stat
        if (stat(argv[1], &stat_buffer) == -1)
        {
            printf("Couldn't stat file %s", argv[1]);
            return -1;
        }
        else
        {
            printf("Current file mode: %o\n", stat_buffer.st_mode);
        }
        //modify file mode arg
        if (chmod(argv[1], mode) != -1)
        {
            if (stat(argv[1], &stat_buffer) == -1)
            {
                printf("Couldn't stat file %s", argv[1]);
                return -1;
            }
            printf("Permissions have changed: %o (%s)\n", stat_buffer.st_mode, argv[2]);
        }
        else
        {
            printf("Permission have not changed");
            return -1;
        }
    }
    else
    {
        printf("File %s does not exists", argv[1]);
        return -1;
    }
    return 0;
}