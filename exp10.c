#include <stdio.h>
#include <stdlib.h>

void fcfs(int nf, int np, int pages[])
{
    int frames[nf];
    for (int i = 0; i < nf; i++)
        frames[i] = -1;

    int pf = 0, last = 0;
    for (int i = 0; i < np; i++)
    {
        int found = 0;
        int currentpage = pages[i];

        for (int j = 0; j < nf; j++)
        {
            if (frames[j] == currentpage)
            {
                found = 1;
                break;
            }
        }

        if (found == 0)
        {
            frames[last] = currentpage;
            last = (last + 1) % nf;
            pf++;
        }

        printf("Page allocation of page string %d: ", currentpage);
        for (int j = 0; j < nf; j++)
        {
            if (frames[j] == -1)
                printf("- ");
            else
                printf("%d ", frames[j]);
        }

        if (found == 1)
            printf(" No Page Fault\n");
        else
            printf(" Page Fault\n");
    }
    printf("Total no of page faults: %d\n", pf);
}

void lru(int nf, int np, int pages[])
{
    int frames[nf], temp[nf];
    for (int i = 0; i < nf; i++)
        frames[i] = -1;

    int pf = 0;
    for (int n = 0; n < np; n++)
    {
        int a = 0, b = 0;

        for (int m = 0; m < nf; m++)
        {
            if (frames[m] == pages[n])
            {
                a = 1;
                b = 1;
                break;
            }
        }

        if (a == 0)
        {
            for (int m = 0; m < nf; m++)
            {
                if (frames[m] == -1)
                {
                    frames[m] = pages[n];
                    b = 1;
                    pf++;
                    break;
                }
            }
        }

        if (b == 0)
        {
            for (int m = 0; m < nf; m++)
            {
                temp[m] = 0;
            }

            for (int k = n - 1, l = 1; l <= nf - 1; l++, k--)
            {
                for (int m = 0; m < nf; m++)
                {
                    if (frames[m] == pages[k])
                    {
                        temp[m] = 1;
                    }
                }
            }

            for (int m = 0; m < nf; m++)
            {
                if (temp[m] == 0)
                {
                    frames[m] = pages[n];
                    pf++;
                    break;
                }
            }
        }

        printf("Page allocation of page string %d: ", pages[n]);
        for (int j = 0; j < nf; j++)
        {
            if (frames[j] == -1)
                printf("X ");
            else
                printf("%d ", frames[j]);
        }

        if (a == 0 || b == 0)
            printf(" Page Fault\n");
        else
            printf(" No Page Fault\n");
    }
    printf("Total no of page faults: %d\n", pf);
}

void opt(int nf, int np, int pages[])
{
    int frames[nf];
    for (int i = 0; i < nf; i++)
        frames[i] = -1;

    int pf = 0;
    for (int i = 0; i < np; i++)
    {
        int found = 0;
        int currentpage = pages[i];
        for (int j = 0; j < nf; j++)
        {
            if (frames[j] == currentpage)
            {
                found = 1;
                break;
            }
        }

        if (found == 0)
        {
            int nextOccurrences[nf];
            for (int j = 0; j < nf; j++)
            {
                int nextOccurrence = np;
                for (int k = i + 1; k < np; k++)
                {
                    if (pages[k] == frames[j])
                    {
                        nextOccurrence = k;
                        break;
                    }
                }
                nextOccurrences[j] = nextOccurrence;
            }

            int pageToReplaceIndex = 0;
            int farthestFutureIndex = 0;
            for (int j = 0; j < nf; j++)
            {
                if (nextOccurrences[j] > farthestFutureIndex)
                {
                    farthestFutureIndex = nextOccurrences[j];
                    pageToReplaceIndex = j;
                }
            }
            frames[pageToReplaceIndex] = currentpage;
            pf++;
        }

        printf("Page allocation of page string %d: ", currentpage);
        for (int j = 0; j < nf; j++)
        {
            if (frames[j] == -1)
                printf("X ");
            else
                printf("%d ", frames[j]);
        }

        if (found == 0)
            printf(" Page Fault\n");
        else
            printf(" No Page Fault\n");
    }
    printf("Total no of page faults: %d\n", pf);
}

int main()
{
    int choice, nf, np;
    printf("Enter the total no of frames: ");
    scanf("%d", &nf);
    printf("Enter the total no of pages: ");
    scanf("%d", &np);

    int pages[np];
    printf("Enter the page string: ");
    for (int i = 0; i < np; i++)
    {
        scanf("%d", &pages[i]);
    }

    while (1)
    {
        printf("\nMenu:\n");
        printf("1. FCFS (First-Come, First-Served)\n");
        printf("2. LRU (Least Recently Used)\n");
        printf("3. Optimal\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            fcfs(nf, np, pages);
            break;
        case 2:
            lru(nf, np, pages);
            break;
        case 3:
            opt(nf, np, pages);
            break;
        case 4:
            exit(0);
        default:
            printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}
