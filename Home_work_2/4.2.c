#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>

int my_double_ls(const char *name)
{
    struct dirent *d;
    struct stat stat_buffer;
    DIR *dp;

    if ((dp = opendir(name)) == NULL)
        return -1;

    while (d = readdir(dp))
    {
        if (d->d_ino != 0)
        {
            if (stat(d->d_name, &stat_buffer) == -1)
            {
                printf("Couldn't stat file %s", d->d_name);
                return -1;
            }
            //if file is DIRECTORY
            if (S_ISDIR(stat_buffer.st_mode))
            {
                printf("%s *\n", d->d_name);
            }
            else
            {
                printf("%s\n", d->d_name);
            }
        }
    }
    rewinddir(dp);

    while (d = readdir(dp))
    {
        if (d->d_ino != 0)
        {
            if (stat(d->d_name, &stat_buffer) == -1)
            {
                printf("Couldn't stat file %s", d->d_name);
                return -1;
            }
            //if file is DIRECTORY
            if (S_ISDIR(stat_buffer.st_mode))
            {
                printf("%s *\n", d->d_name);
            }
            else
            {
                printf("%s\n", d->d_name);
            }
        }
    }

    closedir(dp);
    return 0;
}

int main(int argc, char *argv[])
{
    my_double_ls(argv[1]);

    return 0;
}