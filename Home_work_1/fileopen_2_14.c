#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define FILENAMESIZE 1024
void checkfd(int flag)
{
    if (flag > 0)
    {
        printf("File open succeed\n");
    }else{
        printf("-1\n");
    }
}
int main()
{
    char filename[1024];
    char flag[3];
    int fd = -1;
    printf("Enter File Name: ");
    scanf("%s", filename);
    printf("Enter Open Flag\n Available flags\n r: Read Only\nw: Write Only\nrw:Read and Write Only\na: append on EOF\n");
    scanf("%s", flag);

    if (flag[0] == 'r')
    {
        if (sizeof(flag) > 1)
        {
            if (flag[1] == 'w')
            {

                fd = open(filename, O_WRONLY);
                checkfd(fd);
                return 0;
            }
        }
        else
        {
            fd = open(filename, O_RDONLY);
        }
    }
    else if (flag[0] == 'w')
    {
        fd = open(filename, O_WRONLY);
    }
    if (flag[0] == 'a')
    {
        fd = open(filename, O_WRONLY | O_APPEND);
    }

    checkfd(fd);
    return 0;
}