#include <stdio.h>
#include <string.h>

struct process
{
    char name[20];
    int at, bt, ct, wt, tat, rt, priority;
    int status, remaining;
} p[20];

void getProcessDetails(int n, int isPriority)
{
    printf("\n=== Enter Process Names ===\n");
    for (int i = 0; i < n; i++)
    {
        printf("Process %d name: ", i + 1);
        scanf("%s", p[i].name);
    }

    printf("\n=== Enter Arrival Times ===\n");
    for (int i = 0; i < n; i++)
    {
        printf("Arrival time for %s: ", p[i].name);
        scanf("%d", &p[i].at);
    }

    printf("\n=== Enter Burst Times ===\n");
    for (int i = 0; i < n; i++)
    {
        printf("Burst time for %s: ", p[i].name);
        scanf("%d", &p[i].bt);
        p[i].remaining = p[i].bt;
        p[i].status = 0;
    }

    if (isPriority)
    {
        printf("\n=== Enter Priorities (Lower number = Higher priority) ===\n");
        for (int i = 0; i < n; i++)
        {
            printf("Priority for %s: ", p[i].name);
            scanf("%d", &p[i].priority);
        }
    }
}

void displayResults(int n)
{
    float avg_wt = 0, avg_tat = 0;
    printf("\nProcess\tAT\tBT\tCT\tWT\tTAT");
    if (p[0].priority != 0)
        printf("\tPriority");
    printf("\n");

    for (int i = 0; i < n; i++)
    {
        printf("%s\t%d\t%d\t%d\t%d\t%d",
               p[i].name, p[i].at, p[i].bt, p[i].ct, p[i].wt, p[i].tat);
        if (p[0].priority != 0)
            printf("\t%d", p[i].priority);
        printf("\n");
        avg_wt += p[i].wt;
        avg_tat += p[i].tat;
    }
    printf("\nAverage WT: %.2f", avg_wt / n);
    printf("\nAverage TAT: %.2f\n", avg_tat / n);
}

void fcfs(int n)
{
    int current_time = 0;
    for (int i = 0; i < n; i++)
    {
        if (current_time < p[i].at)
            current_time = p[i].at;
        p[i].ct = current_time + p[i].bt;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        current_time = p[i].ct;
    }
}

void sjf(int n)
{
    int completed = 0, current_time = 0;
    while (completed < n)
    {
        int shortest = -1;
        int min_bt = 9999;

        for (int i = 0; i < n; i++)
        {
            if (p[i].at <= current_time && p[i].status == 0)
            {
                if (p[i].bt < min_bt)
                {
                    min_bt = p[i].bt;
                    shortest = i;
                }
            }
        }

        if (shortest == -1)
        {
            current_time++;
        }
        else
        {
            p[shortest].ct = current_time + p[shortest].bt;
            p[shortest].tat = p[shortest].ct - p[shortest].at;
            p[shortest].wt = p[shortest].tat - p[shortest].bt;
            p[shortest].status = 1;
            completed++;
            current_time = p[shortest].ct;
        }
    }
}

void priority_scheduling(int n)
{
    int completed = 0, current_time = 0;

    while (completed < n)
    {
        int selected = -1;
        int highest_priority = 999999;

        // Find process with highest priority (lowest priority number)
        for (int i = 0; i < n; i++)
        {
            if (p[i].at <= current_time && p[i].status == 0)
            {
                if (p[i].priority < highest_priority)
                {
                    highest_priority = p[i].priority;
                    selected = i;
                }
                // If priorities are equal, choose the one that arrived first
                else if (p[i].priority == highest_priority &&
                         p[i].at < p[selected].at)
                {
                    selected = i;
                }
            }
        }

        if (selected == -1)
        {
            current_time++;
        }
        else
        {
            p[selected].ct = current_time + p[selected].bt;
            p[selected].tat = p[selected].ct - p[selected].at;
            p[selected].wt = p[selected].tat - p[selected].bt;
            p[selected].status = 1;
            completed++;
            current_time = p[selected].ct;
        }
    }
}
void roundRobin(int n, int quantum)
{
    int completed = 0, current_time = 0, i = 0;
    int queue[20], front = 0, rear = 0;
    int visited[20] = {0}; // Track if a process has entered the queue

    for (int i = 0; i < n; i++)
        visited[i] = 0; // Initialize tracking array

    // Initially, push all processes that have arrived at time 0 into the queue
    for (int i = 0; i < n; i++)
    {
        if (p[i].at == 0)
        {
            queue[rear++] = i;
            visited[i] = 1;
        }
    }

    while (completed < n)
    {
        if (front == rear) // No process is in the queue, CPU is idle
        {
            current_time++;
            // Check for newly arrived processes
            for (int i = 0; i < n; i++)
            {
                if (p[i].at == current_time && !visited[i])
                {
                    queue[rear++] = i;
                    visited[i] = 1;
                }
            }
            continue;
        }

        int idx = queue[front++];
        if (p[idx].remaining > quantum)
        {
            current_time += quantum;
            p[idx].remaining -= quantum;
        }
        else
        {
            current_time += p[idx].remaining;
            p[idx].ct = current_time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            p[idx].remaining = 0;
            completed++;
        }

        // Check for newly arrived processes at the current time
        for (int i = 0; i < n; i++)
        {
            if (p[i].at <= current_time && !visited[i])
            {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }

        // If the current process is not yet finished, push it back into the queue
        if (p[idx].remaining > 0)
        {
            queue[rear++] = idx;
        }
    }
}

int main()
{
    int n, choice, quantum;

    while (1)
    {
        printf("\n1. FCFS\n2. SJF\n3. Priority Scheduling\n4. Round Robin\n5. Exit\nChoice: ");
        scanf("%d", &choice);

        if (choice == 5)
            break;

        printf("Enter number of processes: ");
        scanf("%d", &n);

        getProcessDetails(n, choice == 3);

        switch (choice)
        {
        case 1:
            fcfs(n);
            break;
        case 2:
            sjf(n);
            break;
        case 3:
            priority_scheduling(n);
            break;
        case 4:
            printf("Enter time quantum: ");
            scanf("%d", &quantum);
            roundRobin(n, quantum);
            break;
        }

        displayResults(n);
    }
    return 0;
}