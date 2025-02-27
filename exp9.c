#include <stdio.h>

int block[20], process[10], isAllocated[20] = {0}, allocated[20], b, p, choice, flag = 0;

void firstFit()
{
    for (int i = 0; i < p; i++)
    {
        allocated[i] = -999; // Default to not allocated
    }

    for (int i = 0; i < p; i++)
    {
        for (int j = 0; j < b; j++)
        {
            if (process[i] <= block[j] && isAllocated[j] == 0)
            {
                allocated[i] = block[j]; // Assign block
                isAllocated[j] = 1;      // Mark block as allocated
                break;                   // Stop after finding first fit
            }
        }
    }
    printf("\nFIRST FIT Allocation Done\n");
}

void bestFit()
{
    for (int i = 0; i < p; i++)
    {
        allocated[i] = -999; // Default to not allocated
        int bestIdx = -1;

        for (int j = 0; j < b; j++)
        {
            if (process[i] <= block[j] && isAllocated[j] == 0)
            {
                if (bestIdx == -1 || block[j] < block[bestIdx])
                {
                    bestIdx = j;
                }
            }
        }

        if (bestIdx != -1)
        {
            allocated[i] = block[bestIdx];
            isAllocated[bestIdx] = 1;
        }
    }
    printf("\nBEST FIT Allocation Done\n");
}

void worstFit()
{
    for (int i = 0; i < p; i++)
    {
        allocated[i] = -999; // Default to not allocated
        int worstIdx = -1;

        for (int j = 0; j < b; j++)
        {
            if (process[i] <= block[j] && isAllocated[j] == 0)
            {
                if (worstIdx == -1 || block[j] > block[worstIdx])
                {
                    worstIdx = j;
                }
            }
        }

        if (worstIdx != -1)
        {
            allocated[i] = block[worstIdx];
            isAllocated[worstIdx] = 1;
        }
    }
    printf("\nWORST FIT Allocation Done\n");
}

void display()
{
    printf("\nProcess#\tProcess Size\tBlock Allocated\n");
    for (int i = 0; i < p; i++)
    {
        if (allocated[i] == -999)
        {
            printf("%d\t\t%d\t\tNot Allocated\n", i, process[i]);
        }
        else
        {
            printf("%d\t\t%d\t\t%d\n", i, process[i], allocated[i]);
        }
    }
}

int main()
{
    printf("Enter the Number of Blocks: ");
    scanf("%d", &b);
    printf("Enter the Size of Each Block:\n");
    for (int i = 0; i < b; i++)
    {
        printf("B%d: ", i);
        scanf("%d", &block[i]);
        isAllocated[i] = 0; // Ensure all blocks start as unallocated
    }

    printf("Enter the Number of Processes: ");
    scanf("%d", &p);
    printf("Enter the Size of Each Process:\n");
    for (int i = 0; i < p; i++)
    {
        printf("P%d: ", i);
        scanf("%d", &process[i]);
    }

    while (choice != 4)
    {
        printf("\nChoose Allocation Method: \n1. First Fit\n2. Best Fit\n3. Worst Fit\n4. Exit\n");
        printf("Enter a choice: ");
        scanf("%d", &choice);

        for (int i = 0; i < b; i++) // Reset block allocation before each method
            isAllocated[i] = 0;

        switch (choice)
        {
        case 1:
            firstFit();
            display();
            break;
        case 2:
            bestFit();
            display();
            break;
        case 3:
            worstFit();
            display();
            break;
        case 4:
            printf("\nExiting Program...\n");
            break;
        default:
            printf("\nInvalid choice! Try again.\n");
        }
    }

    return 0;
}
