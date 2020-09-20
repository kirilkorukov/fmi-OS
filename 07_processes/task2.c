/*
    2. Да се напише програма на C, която изпълнява команда ls с точно един аргумент.
*/

#include <unistd.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        errx(2,"We need exactly one argument");
    }

    if(execl("/bin/ls", "my_command", argv[1], (char*)NULL) == -1)
    {
        err(3, "could not execute ls");
    }
    else
    {
        printf("won't be printed");
    }

    exit(1);
}
~              
