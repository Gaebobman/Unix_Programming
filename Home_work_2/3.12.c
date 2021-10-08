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
    if (access(argv[2], F_OK) == -1)
    {
        printf("File %s does not exists", argv[2]);
        return -1;
    }
    //if file exists, Check READ PERMISSION on file
    // if (access(argv[1], R_OK) == -1)
    // {
    //     printf("You don't have READ PERMISSION on %s", argv[1]);
    //     return -1;
    // }
    //if file exists, Check WRITE PERMISSION on file
    // if (access(argv[1], W_OK) == -1)
    // {
    //     printf("You don't have WRITE PERMISSION on %s", argv[1]);
    //     return -1;
    // }
    if (argv[1][0] == '0')
    { //If argv[2] is in 0XXX format
        //convert arg[2] to mode_t, char* => mode_t(unsigned int)
        char S = argv[1][0] - '0';
        char USER_CHAR = argv[1][1] - '0';
        char GROUP_CHAR = argv[1][2] - '0';
        char OTHER_CHAR = argv[1][3] - '0';

        mode = OTHER_CHAR;
        mode |= GROUP_CHAR << 3;
        mode |= USER_CHAR << 6;
        mode |= S << 9;

        //store file stat
        if (stat(argv[2], &stat_buffer) == -1)
        {
            printf("Couldn't stat file %s", argv[2]);
            return -1;
        }
        else
        {
            printf("Current file mode: %o\n", stat_buffer.st_mode);
        }
        //modify file mode arg
        if (chmod(argv[2], mode) != -1)
        {
            if (stat(argv[2], &stat_buffer) == -1)
            {
                printf("Couldn't stat file %s", argv[2]);
                return -1;
            }
            printf("Permissions have changed: %o (%s)\n", stat_buffer.st_mode, argv[1]);
        }
        else
        {
            printf("Permission have not changed");
            return -1;
        }
    }
    else
    { // if argv[1] in <U|G|O> <+|-> <R|W|X> format
        //check permssion is USER || GROUP || OTHERS
        const char PERMISSION_GROUP = argv[1][0];
        const char PERMISSION_ADDMINUS = argv[1][1];

        int perm_length = 0;
        while (argv[1][perm_length] != '\0')
        {
            perm_length++;
        }
        for (int i = perm_length - 1; i >= 2; i--)
        { //mode set
            int tmp_mode = argv[1][i] - 0;
            mode |= 0 << 9;
            switch (tmp_mode)
            {
            case 'r' - 0:
                mode += 4;
                break;
            case 'w' - 0:
                mode += 2;
                break;
            case 'x' - 0:
                mode += 1;
                break;
            }
        }
        //shift mode bits for target permission group
        int tmp_permission_group = argv[1][0] - 0;
        switch (tmp_permission_group)
        {
        case 'u' - 0:
        case 'U' - 0:
            mode = mode << 6;
            break;
        case 'g' - 0:
        case 'G' - 0:
            mode = mode << 3;
            break;
        case 'o' - 0:
        case 'O' - 0:
            // We don't have to shift for others permission(these are 3 LSB)
            break;
        }

        //get current mode
        if (stat(argv[2], &stat_buffer) == -1)
        {
            printf("Couldn't stat file %s", argv[2]);
            return -1;
        }
        else
        {
            printf("Current file mode: %o\n", stat_buffer.st_mode);
        }

        //check add or minus of permission
        if (argv[1][1] == '-')
        {
            //if minus of permission
            stat_buffer.st_mode -= mode;
        }
        else if (argv[1][1] == '+')
        {
            stat_buffer.st_mode |= mode;
        }
        else
        {
            printf("Invalid arg[1], use '+' or '-'\n");
            return -1;
        }

        if (chmod(argv[2], stat_buffer.st_mode) != -1)
        {
            printf("Permissions have changed \n");
        }
    }
    return 0;
}