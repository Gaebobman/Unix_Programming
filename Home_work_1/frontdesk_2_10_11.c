#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define NAMELENGTH 41
#define NROOMS 10
#define OPEN_ERROR -1
#define LSEEK_ERROR -2
#define READ_ERROR -3
#define NO_AVAILABLE_ROOM -1111

char namebuf[NAMELENGTH];
int infile = -1;

char *getoccupier(int roomno)
{
    off_t offset;
    ssize_t nread;
    if (infile == -1 && (infile = open("residents", O_RDONLY)) == -1)
    {
        return (NULL);
    }
    offset = (roomno - 1) * NAMELENGTH;

    if (lseek(infile, offset, SEEK_SET) == -1)
        return (NULL);
    if ((nread = read(infile, namebuf, NAMELENGTH)) <= 0)
        return (NULL);

    namebuf[nread - 1] = '\0';
    return (namebuf);
}

int freeroom(int room)
{
    // infile = -1;
    if (infile == -1 && (infile = open("residents", O_RDWR)) == -1)
        //open error
        return -1;

    if (lseek(infile, (room - 1) * NAMELENGTH, SEEK_SET) == -1)
        //lseek error
        return -2;
    else
    {
        for (int i = 0; i < 40; i++)
            namebuf[i] = ' ';
        namebuf[NAMELENGTH - 1] = '\n';
        write(infile, namebuf, NAMELENGTH);
    }
    close(infile);
    return 0;
}

int addguest(int room, char *guestName)
{
    off_t offset;
    ssize_t nread;

    infile = -1;
    if (infile == -1 && (infile = open("residents", O_RDWR)) == -1)
        return OPEN_ERROR;

    if (lseek(infile, (room - 1) * NAMELENGTH, SEEK_SET) == -1)
        return LSEEK_ERROR;

    if ((nread = read(infile, namebuf, NAMELENGTH)) < 0)
        return READ_ERROR;

    if (lseek(infile, -NAMELENGTH, SEEK_CUR) == -1)
        return LSEEK_ERROR;

    if (namebuf[40] == ' ')
    {
        guestName[nread - 1] = '\n';
        write(infile, guestName, NAMELENGTH);
    }
    else
    {
        printf("This room is already ocuppied\n");
        return NO_AVAILABLE_ROOM;
    }

    close(infile);
    return 0;
}

int findfree()
{
    off_t offset;
    ssize_t nread;

    infile = -1;
    if (infile == -1 && (infile = open("residents", O_RDWR)) == -1)
        return OPEN_ERROR;

    for (int i = 0; i < 10; i++)
    {
        namebuf[0] = ' ';
        if (lseek(infile, i * NAMELENGTH, SEEK_SET) == -1)
            return LSEEK_ERROR;

        if ((nread = read(infile, namebuf, NAMELENGTH)) < 0)
            return READ_ERROR;

        if (namebuf[0] == ' ')
            return i;
    }
    return NO_AVAILABLE_ROOM;
}
int main()
{
    int command = 0;
    int roomnumber = 0;
    char guestname[NAMELENGTH];
    while (command != -1)
    {
        printf("\n######################\n1. getoccupier\n2. freeroom\n3.addguest\n4.findfree\n######################\nEnter service number, -1 to exit: ");
        scanf("%d", &command);
        switch (command)
        {
        case 1:
            printf("Enter Room Number: ");
            scanf("%d", &roomnumber);
            printf("\n");
            if (getoccupier(roomnumber) == NULL)
            {
                printf("This room is Empty\n");
                printf("\n######################\n");
            }
            else
            {
                printf("This Room is Occupied by: %s", getoccupier(roomnumber));
                printf("\n######################\n");
            }
            break;
        case 2:
            printf("Enter Room Number: ");
            printf("\n");
            scanf("%d", &roomnumber);
            if (freeroom(roomnumber) > 0)
            {
                printf("This room is no longer occupied.\n");
                printf("\n######################\n");
            }
            else
            {
                printf("An error occured while freeing room\n");
                printf("\n######################\n");
            }
            break;
        case 3:
            printf("Enter Room Number And Guest Name\nRoom Number: ");
            scanf("%d", &roomnumber);
            printf("Guest Name: ");
            scanf("%s", guestname);
            if (addguest(roomnumber, guestname) == 0)
            {
                printf("You've made a reservation successfully.\n");
                printf("\n######################\n");
            }
            else
            {
                printf("Reservation failed.\n");
                printf("\n######################\n");
            }
        case 4:
            if (findfree() == NO_AVAILABLE_ROOM)
            {
                printf("All rooms are occupied.\n");
                printf("\n######################\n");
            }
            else
            {
                printf("Available fastest room number: %d\n", findfree() +1);
                printf("\n######################\n");
            }
            break;
        }
    }
    return 0;
}