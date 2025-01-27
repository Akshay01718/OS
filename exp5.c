#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int buffer[5], in = 0, out = 0, n;

int producer()
{
    if ((in + 1) % 5 == out)
    {
        printf("Buffer is full\n");
    }
    else
    {
        in = (in + 1) % 5;
        printf("Enter the value to be produced: \n");
        scanf("%d", &n);
        buffer[in] = n;
    }
}

int consumer()
{
    if (out == in)
    {
        printf("Buffer is empty\n");
    }
    else
    {
        out = (out + 1) % 5;
        printf("%i is consumed\n", buffer[out]);
    }
}

void print_memory()
{
    int i = out;
    while (i != in)
    {
        i = (i + 1) % 5;
        printf("%i\t ", buffer[i]);
    }
    printf("\n");
}
void main()
{
    int o;
    while (true)
    {
        printf("MENU:\n1. Produce\n2. Consume\n3. Print Shared Memory\n4. EXIT\nEnter Your Option:\n");
        scanf("%d", &o);
        switch (o)
        {
        case 1:
            producer();
            break;
        case 2:
            consumer();
            break;
        case 3:
            print_memory();
            break;
        case 4:
            printf("\nExiting...\n");
            exit(0);
        }
    }
}
