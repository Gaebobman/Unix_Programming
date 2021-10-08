#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>

#define SIZE 1024

char *USAGE = "Usage: 3.10.c 'filename'";
struct stat stat_buffer;

int main(int argc, char *argv[])
{
    char time_buff[20];
    if (argc != 2)
    {
        perror(USAGE);
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
        else
        {
            //save Last modified time and Compare it 30 second later
            if (stat(argv[1], &stat_buffer) == -1)
            {
                printf("Couldn't stat file %s", argv[1]);
                return -1;
            }
            else
            {
                // time_t to YYYY-mm-dd HH:MM:SS format REFERENCE: "https://stackoverflow.com/questions/3053999/c-convert-time-t-to-string-with-format-yyyy-mm-dd-hhmmss"
                time_t last_modified_time = stat_buffer.st_mtime;
                strftime(time_buff, 20, "%Y-%m-%d %H:%M:%S", localtime(&last_modified_time));
                printf("last modified time: %s\n", time_buff);
                while (1)
                {
                    time_t prev_mod_time = last_modified_time;
                    //Update stat
                    if (stat(argv[1], &stat_buffer) == -1)
                    {
                        printf("Couldn't stat file %s", argv[1]);
                        return -1;
                    }
                    last_modified_time = stat_buffer.st_mtime;
                    sleep(5);
                    if (last_modified_time == prev_mod_time)
                    { //if last modified time is same, continue
                        printf("Not modified yet \n");
                    }
                    else
                    { //if last modified time is different
                        printf("\n############################\nMODIFICATION DETECTED !!!\n############################\n");
                        break;
                    }
                    last_modified_time = stat_buffer.st_mtime;
                }
                //when program detected modification on file, COPY it to its standart output
                int fd = open(argv[1], O_RDONLY);
                ssize_t nread;
                char buf[SIZE];
                while ((nread = read(fd, buf, SIZE)) > 0)
                    write(1, buf, nread);
                printf("\nCOPY SUCCEEDDED\n");
            }
        }
    }
    else
    {
        perror("File does not exists!!!");
        return -1;
    }

    return 0;
}