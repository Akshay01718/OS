#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    pid_t q;

    printf("\nBefore fork()\n");
    q = fork();

    if (q == 0)
    { // Child
        printf("I am Child having id %d\n", getpid());
        printf("My Parent's id is %d\n", getppid());
        sleep(10);
        printf("\nBefore exec\n");
        execl("/bin/ls", "ls", "-a", NULL);
        printf("\nAfter exec\n");
    }
    else
    { // Parent
        wait(NULL);
        printf("My Child's id is %d\n", q);
        printf("I am Parent having id %d\n", getpid());
    }

    printf("\nCommon\n");

    return 0;
}
