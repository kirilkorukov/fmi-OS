/*
    Реализирайте команда head без опции (т.е. винаги да извежда
    на стандартния изход само първите 10 реда от съдържанието на
    файл подаден като първи параматър)
*/
#include <unistd.h>
#include <err.h>
#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
    if(argc != 2)
    {
        errx(1, "We need one argument file name");
    }

    int fd;
    if((fd = open(argv[1], O_RDONLY)) == -1){
        err(2, "Error opening file for reading");
    }

    char c;
    int currentLine = 0;
    int lines = 10;

    while(read(fd, &c, 1) == 1)
    {
        write(1, &c, 1);
        if(c == '\n')
        {
            currentLine++;
            if(currentLine ==  lines) break; // because we start at zero
        }
    }

    close(fd);

    return 42;
}

