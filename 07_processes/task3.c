#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <err.h>

/*
    3. Да се напише програма на C, която изпълнява команда sleep (за 60 секунди).
*/

int main(void)
{
    const char *command = "/bin/sleep", *arg = "60";
    if(execl(command,"sleeping",arg,(char*)NULL) == -1)
    {
        err(2, "could not execute");
    }
}

