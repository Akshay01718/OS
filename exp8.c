#include <stdio.h>

int main()
{
    int numProcesses, numResources, i, j, k;
    int allocation[20][20], maximum[20][20], available[50], index = 0;

    printf("Enter the Number of Processes: ");
    scanf("%d", &numProcesses);

    printf("Enter the Number of Resources: ");
    scanf("%d", &numResources);

    printf("Enter the Allocation Matrix:\n");
    for (i = 0; i < numProcesses; i++)
    {
        for (j = 0; j < numResources; j++)
        {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter the Maximum Matrix:\n");
    for (i = 0; i < numProcesses; i++)
    {
        for (j = 0; j < numResources; j++)
        {
            scanf("%d", &maximum[i][j]);
        }
    }

    printf("Enter the Available Matrix:\n");
    for (i = 0; i < numResources; i++)
    {
        scanf("%d", &available[i]);
    }

    int finish[numProcesses], safeSequence[numProcesses];
    int work[numResources], need[numProcesses][numResources];

    // Calculating the NEED matrix
    printf("NEED Matrix is:\n");
    for (i = 0; i < numProcesses; i++)
    {
        printf("\n");
        for (j = 0; j < numResources; j++)
        {
            need[i][j] = maximum[i][j] - allocation[i][j];
            printf("%d ", need[i][j]);
        }
    }

    // Initializing Work = Available
    for (i = 0; i < numResources; i++)
    {
        work[i] = available[i];
    }

    // Initializing Finish Array to 0
    for (i = 0; i < numProcesses; i++)
    {
        finish[i] = 0;
    }

    // Safety Algorithm
    for (k = 0; k < numProcesses; k++)
    {
        for (i = 0; i < numProcesses; i++)
        {
            if (finish[i] == 0)
            {
                int flag = 0;
                for (j = 0; j < numResources; j++)
                {
                    if (need[i][j] > work[j])
                    {
                        flag = 1;
                        break;
                    }
                }

                if (flag == 0)
                {
                    safeSequence[index++] = i;
                    for (j = 0; j < numResources; j++)
                    {
                        work[j] += allocation[i][j];
                    }
                    finish[i] = 1;
                }
            }
        }
    }

    printf("\nFollowing is the SAFE Sequence:\n");
    for (i = 0; i < numProcesses; i++)
    {
        printf("%d ", safeSequence[i]);
    }

    return 0;
}
