/* Напишете програма, която приема точно 2 аргумента. Първият може да бъде само --min, --max или --print (вижте man 3 strcmp). Вторият аргумент е двоичен файл, в който има записани цели неотрицателни двубайтови числа (uint16_t - вижте man stdint.h). Ако първият аргумент е:
--min - програмата отпечатва кое е най-малкото число в двоичния файл.
--max - програмата отпечатва кое е най-голямото число в двоичния файл.
--print - програмата отпечатва на нов ред всяко число.
Използвайте двоичния файл binary/dump или генерирайте сами такъв (правилно подравнен).
*/

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <err.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdint.h>

int main(int argc, char* argv[])
{
if(argc != 3)
{
	errx(1, "We need two arguments");
}	

if(!(strcmp(argv[1],"--min") == 0 || strcmp(argv[1],"--max") || strcmp(argv[1], "--print")))
{
	errx(2, "Available options for first argument: --min, --max, --print");
}

struct stat st;
if(stat(argv[2], &st) == -1)
{
	err(3, "Cannot stat file %s", argv[2]);
}
if(st.st_size == 0)
{
	err(4, "File %s is empty", argv[2]);
}

int fd;
fd = open(argv[2], O_RDONLY);
if(fd == -1)
{
	err(5, "error opening file %s for reading", argv[1]);
}


uint16_t min_number = INT16_MAX;
uint16_t max_number = 0;
uint16_t buf;
while(1)
{
	int read_size = read(fd, &buf, sizeof(uint16_t));
	if(read_size == 0)
	{
		break;
	}
	else if(read_size == -1)
	{
		const int olderrno = errno;
		close(fd);
		errno = olderrno;
		err(6, "error reading file");
	}

	if(strcmp(argv[1], "--print") == 0)
	{
		printf("%d\n", (uint16_t)buf);
	}
	else if(strcmp(argv[1], "--max") == 0)
	{
		if(buf > max_number) max_number = buf;
	}
	else
	{
		if(buf < min_number) min_number = buf;
	}
}

if(strcmp(argv[1], "--max") == 0)
{
	printf("Max number is: %d\n", buf);
}
else if(strcmp(argv[1], "--min") == 0)
{
	printf("Min number is: %d\n", buf);
}

close(fd);
exit(1);
}

