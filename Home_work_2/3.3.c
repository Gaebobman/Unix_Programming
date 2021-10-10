#include <stdio.h>

#define PERM_LENGTH 9
#define OCT_PERM_LENGTH 4

const int WEIGHT[] = {4, 2, 1, 4, 2, 1, 4, 2, 1};
const char PERMSET[] = {'r', 'w', 'x', 'r', 'w', 'x', 'r', 'w', 'x'};

void lsoct(char *permission, int *oct_permission)
{
    // for(int i = 0 ; i< PERM_LENGTH; i++){
    //     printf("%c", permission[i]);
    // }

    for (int i = 0; i <= PERM_LENGTH; i++)
    {
        if (permission[i] != '-')
        {
            switch (i)
            {
            case 0:
            case 1:
            case 2:
                oct_permission[1] += WEIGHT[i];
                break;
            case 3:
            case 4:
            case 5:
                oct_permission[2] += WEIGHT[i];
                break;
            case 6:
            case 7:
            case 8:
                oct_permission[3] += WEIGHT[i];
                break;
            default:
                break;
            }
        }
    }
    printf("lsoct: ");
    for (int i = 0; i < OCT_PERM_LENGTH; i++)
    {
        printf("%d", oct_permission[i]);
    }
    printf("\n");
}

void octls(int *oct_permission)
{
    printf("octls: ");
    for (int i = 1; i < OCT_PERM_LENGTH; i++)
    {
        switch (oct_permission[i])
        {
        case 0:
            printf("---");
            break;
        case 1:
            printf("--x");
            break;
        case 2:
            printf("-w-");
            break;
        case 3:
            printf("-wx");
            break;
        case 4:
            printf("r--");
            break;
        case 5:
            printf("r-x");
            break;
        case 6:
            printf("rw-");
            break;
        case 7:
            printf("rwx");
            break;
        default:
            break;
        }
    }
    printf("\n");
}

int main()
{
    char permission[PERM_LENGTH] = {'-'};
    int oct_permission[OCT_PERM_LENGTH] = {0};
    printf("Enter set of permission: ");
    scanf("%s", permission);
    lsoct(permission, oct_permission);
    octls(oct_permission);

    return 0;
}