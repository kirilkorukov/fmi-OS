/*
    8. Да се напише програма на С, която получава като параметър име на файл. 
    Създава детински процес, който записва стринга foobar във файла (ако не съществува, го създава, 
    в противен случай го занулява), след което процеса родител прочита записаното във файла съдържание 
    и го извежда на стандартния изход, добавяйки по един интервал между всеки два символа.
*/

#include <stdlib.h>
#include <unistd.h>
#include <err.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
	if(argc != 2)
		errx(1, "Wanted 1 argument got %d", argc - 1);

	pid_t child_pid = fork();
	if(child_pid == -1)
		err(3, "Error forking");
	if(child_pid == 0)
	{
		int fdw;
		if((fdw = open(argv[1], O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU)) == -1)
			err(2, "error opening for writing");
		if(write(fdw, "foobar", 6) != 6)
		{
			err(4, "Error writing in file");
		}
		close(fdw);
		exit(10);
	}
	else // here else is not needed because of the exit in child
	{
		int child_exit_status;
		if(wait(&child_exit_status) == -1)
			err(5, "error waiting");
		int fdr;
		if((fdr = open(argv[1], O_RDONLY)) == -1)
			err(6, "error opening file for reading");
		char c;
		char blank_space = ' ';
		while(read(fdr, &c, 1) == 1)
		{
			if(c == '\n')
			{
				write(1, &c, 1);
			}
			else
			{
				write(1, &c, 1);
				write(1, &blank_space, 1);
			}
		}
		close(fdr);
		write(1, '\n', 1);
	}	
}

