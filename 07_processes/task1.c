#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <err.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

/*
    1. Да се напише програма на C, която изпълнява команда date.
*/

int main()
{
    if(execl("/bin/date", "current_date", (char*)NULL) == -1)
    {
        err(2, "error executing date");
    }
    else
    {
        printf("Won't be printed because the binary file has different content now");
    }

    exit(1);
}

