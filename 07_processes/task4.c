/*
    4. Да се напише програма на C, която създава процес дете и демонстрира принцина на конкурентност при процесите.
*/
#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
    const int N = 5;

    for(int i = 0; i < N; i++)
    {
    pid_t my_pid = fork();

    if(my_pid == -1)
    {
        err(1, "could not fork");
    }

    if(my_pid > 0)
    {
        printf("parent with pid: %d\n", getpid());
    }
    else
    {
        printf("child with pid: %d\n", getpid());
    }
    }
}

