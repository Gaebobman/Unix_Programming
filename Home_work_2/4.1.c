#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>

#define SKIP 1
int my_double_ls(const char *name, int flag)
{
    struct dirent *d;
    DIR *dp;

    if ((dp = opendir(name)) == NULL)
        return -1;

    while (d = readdir(dp))
    {
        if (d->d_ino != 0)
        {
            if (flag == SKIP && d->d_name[0] == '.')
                continue;
            printf("%s\n", d->d_name);
        }
    }
    rewinddir(dp);

    while (d = readdir(dp))
    {
        if (d->d_ino != 0)
        {
            if (flag == SKIP && d->d_name[0] == '.')
                continue;
            printf("%s\n", d->d_name);
        }
    }

    closedir(dp);
    return 0;
}

int main(int argc, char *argv[])
{
    my_double_ls(argv[1], atoi(argv[2]));

    return 0;
}