#include <stdio.h>
#include <stdlib.h>

struct file
{
    char name[26];
    int start, siz;
    int blocks[20];
};

void linked()
{
    int f[200] = {0}, a, st, n, alloc = 0;
    struct file files[20];
    int nof;

    printf("Enter the number of Files: ");
    scanf("%d", &nof);

    for (int w = 0; w < nof; w++)
    {
        printf("Enter the file name: ");
        scanf("%s", files[alloc].name);
        printf("Enter the starting block: ");
        scanf("%d", &st);
        f[st] = 1;
        printf("Enter the number of blocks: ");
        scanf("%d", &n);
        printf("Enter Block Numbers: ");
        for (int i = 0; i < n; i++)
        {
            scanf("%d", &a);
            f[a] = 1;
            files[alloc].blocks[i] = a;
        }
        files[alloc].start = st;
        files[alloc].siz = n;
        alloc++;
    }
    printf("\nFile\tStart\tSize\tBlocks\n");
    for (int i = 0; i < alloc; i++)
    {
        printf("%s\t%d\t%d\t", files[i].name, files[i].start, files[i].siz);
        printf("%d", files[i].blocks[0]);
        for (int j = 1; j < files[i].siz; j++)
            printf(" --> %d", files[i].blocks[j]);
        printf("\n");
    }
}

void indexed()
{
    int f[200] = {0}, index[50], abcfil[50][3], allocated = 0, ind, n, count;
    int nof;
    printf("Enter the number of Files: ");
    scanf("%d", &nof);
    for (int w = 0; w < nof; w++)
    {
        printf("Enter the index block: ");
        scanf("%d", &ind);
        if (f[ind] == 1)
        {
            printf("%d index is already allocated\n", ind);
            continue;
        }
        printf("Enter blocks occupied by the file: ");
        scanf("%d", &n);
        count = 0;
        printf("Enter blocks of file: ");
        for (int i = 0; i < n; i++)
        {
            scanf("%d", &index[i]);
            if (f[index[i]] == 0)
                count++;
        }
        if (count == n)
        {
            for (int j = 0; j < n; j++)
                f[index[j]] = 1;
            printf("Allocated\n");
            abcfil[allocated][0] = w + 1;
            abcfil[allocated][1] = ind;
            abcfil[allocated][2] = n;
            allocated++;
        }
        else
        {
            printf("File in the index is already allocated\n");
        }
    }
    printf("\nAllocated Blocks\nFile\tIndex\tLength\n");
    for (int i = 0; i < allocated; i++)
        printf("%d\t%d\t%d\n", abcfil[i][0], abcfil[i][1], abcfil[i][2]);
}

void seq()
{
    int files[200] = {0}, abcfiles[32][3];
    int startBlock, len, allocated = 0;
    int n;
    printf("Enter the number of files: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        int flag = 0;
        printf("Enter the starting block and the length of the file %d: ", i + 1);
        scanf("%d%d", &startBlock, &len);
        for (int j = startBlock; j < (startBlock + len); j++)
        {
            if (files[j] == 0)
                flag++;
        }
        if (len == flag)
        {
            for (int k = startBlock; k < (startBlock + len); k++)
            {
                files[k] = 1;
            }
            printf("The file %d is allocated to the disk\n", i + 1);
            abcfiles[allocated][0] = i + 1;
            abcfiles[allocated][1] = startBlock;
            abcfiles[allocated][2] = len;
            allocated++;
        }
        else
        {
            printf("The file %d is not allocated to the disk\n", i + 1);
        }
    }
    printf("\nAllocated Files:\n\nFile No\tStart Block\tLength\n");
    for (int i = 0; i < allocated; i++)
    {
        printf("%d\t%d\t%d\n", abcfiles[i][0], abcfiles[i][1], abcfiles[i][2]);
    }
    int filno;
    printf("\nEnter File Number: ");
    scanf("%d", &filno);
    for (int i = 0; i < allocated; i++)
    {
        if (abcfiles[i][0] == filno)
        {
            printf("File Number: %d\t Space Occupied: %d\n", abcfiles[i][0], abcfiles[i][2]);
            return;
        }
    }
    printf("File Number Not Found!\n");
}

int main()
{
    int op = 0;
    while (op != 4)
    {
        printf("\n1. SEQUENTIAL\n2. INDEXED\n3. LINKED\n4. Exit\nEnter your option: ");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            seq();
            break;
        case 2:
            indexed();
            break;
        case 3:
            linked();
            break;
        case 4:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid option!\n");
        }
    }
    return 0;
}