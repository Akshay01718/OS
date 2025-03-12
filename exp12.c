#include <stdio.h>
#include <stdlib.h>
#include <limits.h> // For INT_MAX

// First Come First Serve (FCFS) Disk Scheduling
void fcfs(int nd, int nr, int requests[], int head)
{
    int cr;
    int st, totst = 0;
    for (int i = 0; i < nr; i++)
    {
        cr = requests[i];
        st = abs(cr - head);
        printf("Head moves from %d to %d | Seek Time = %d\n", head, cr, st);
        totst += st;
        head = cr;
    }
    printf("Total head movement = %d\n", totst);
}

// Shortest Seek Time First (SSTF) Disk Scheduling
void sstf(int nd, int nr, int requests[], int head)
{
    int serviced[nr];
    for (int i = 0; i < nr; i++)
        serviced[i] = 0;

    int st, totst = 0;

    for (int i = 0; i < nr; i++)
    {
        int min_seek = INT_MAX, min_index = -1;
        for (int j = 0; j < nr; j++)
        {
            if (!serviced[j])
            {
                int seek = abs(requests[j] - head);
                if (seek < min_seek)
                {
                    min_seek = seek;
                    min_index = j;
                }
            }
        }
        serviced[min_index] = 1;
        totst += min_seek;
        printf("Head moves from %d to %d | Seek Time = %d\n", head, requests[min_index], min_seek);
        head = requests[min_index];
    }
    printf("Total head movement = %d\n", totst);
}

// SCAN (Elevator) Disk Scheduling
void scan(int nd, int nr, int requests[], int head)
{
    int cr, st, totst = 0;
    requests[nr] = nd - 1; // Add last cylinder to requests
    nr++;

    // Sort requests
    for (int i = 0; i < nr - 1; i++)
    {
        for (int j = 0; j < nr - i - 1; j++)
        {
            if (requests[j] > requests[j + 1])
            {
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }

    int head_index = 0;
    while (head_index < nr && requests[head_index] < head)
    {
        head_index++;
    }

    for (int j = head_index; j < nr; j++)
    {
        cr = requests[j];
        st = abs(cr - head);
        printf("Head moves from %d to %d | Seek Time = %d\n", head, cr, st);
        totst += st;
        head = cr;
    }

    for (int j = head_index - 1; j >= 0; j--)
    {
        cr = requests[j];
        st = abs(cr - head);
        printf("Head moves from %d to %d | Seek Time = %d\n", head, cr, st);
        totst += st;
        head = cr;
    }

    printf("Total head movement = %d\n", totst);
}

// C-SCAN (Circular SCAN) Disk Scheduling
void cscan(int nd, int nr, int requests[], int head)
{
    int cr, st, totst = 0;
    requests[nr] = 0;          // Add first cylinder
    requests[nr + 1] = nd - 1; // Add last cylinder
    nr += 2;

    // Sort requests
    for (int i = 0; i < nr - 1; i++)
    {
        for (int j = 0; j < nr - i - 1; j++)
        {
            if (requests[j] > requests[j + 1])
            {
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }

    int head_index = 0;
    while (head_index < nr && requests[head_index] < head)
    {
        head_index++;
    }

    for (int j = head_index; j < nr; j++)
    {
        cr = requests[j];
        st = abs(cr - head);
        printf("Head moves from %d to %d | Seek Time = %d\n", head, cr, st);
        totst += st;
        head = cr;
    }

    if (head != 0)
    {
        cr = requests[0];
        printf("Head moves from %d to %d (Cyclic Move)\n", head, cr);
        head = cr;
    }

    for (int j = 1; j < head_index; j++)
    {
        cr = requests[j];
        st = abs(cr - head);
        printf("Head moves from %d to %d | Seek Time = %d\n", head, cr, st);
        totst += st;
        head = cr;
    }

    printf("Total head movement = %d\n", totst);
}

// LOOK Disk Scheduling
void look(int nd, int nr, int requests[], int head)
{
    scan(nd, nr, requests, head);
}

// C-LOOK Disk Scheduling
void clook(int nd, int nr, int requests[], int head)
{
    cscan(nd, nr, requests, head);
}

// Main Function
int main()
{
    int nd, nr;
    printf("Enter no of disks: ");
    scanf("%d", &nd);

    printf("Enter no of requests: ");
    scanf("%d", &nr);

    int requests[nr];
    printf("Enter the requests string: ");
    for (int i = 0; i < nr; i++)
        scanf("%d", &requests[i]);

    int head;
    printf("Current position of head: ");
    scanf("%d", &head);

    int choice;
    while (1)
    {
        printf("\nSelect Disk Scheduling Algorithm:\n");
        printf("1. FCFS\n");
        printf("2. SSTF\n");
        printf("3. SCAN\n");
        printf("4. C-SCAN\n");
        printf("5. LOOK\n");
        printf("6. C-LOOK\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            fcfs(nd, nr, requests, head);
            break;
        case 2:
            sstf(nd, nr, requests, head);
            break;
        case 3:
            scan(nd, nr, requests, head);
            break;
        case 4:
            cscan(nd, nr, requests, head);
            break;
        case 5:
            look(nd, nr, requests, head);
            break;
        case 6:
            clook(nd, nr, requests, head);
            break;
        case 7:
            exit(0);
        default:
            printf("Invalid choice! Please select again.\n");
        }
    }

    return 0;
}
