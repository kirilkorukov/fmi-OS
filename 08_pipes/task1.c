/*
T1 - Да се напише програма на C, която приема аргумент - име на файл. Програмата да:
записва във файла 'fo'
създава child процес, който записва 'bar\n'
parent-а, след като изчака child процеса, записва 'o\n'
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char** argv)
{
	if(argc != 2)
	{
		errx(1, "you need to pass one argument");
	}

	const char* foo = "foo\n";
	const char* bar = "bar\n";

	int fd = open(argv[1], O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	if(fd == -1)
	{
		err(2, "error opening the file");
	}

	if(write(fd, foo, 2) != 2)
	{
		const int olderrno = errno;
		close(fd);
		errno = olderrno;
		err(3, "error writing in file");
	}
	
	pid_t child_pid = fork();
	
	printf("Outer Banks\n");
	if(child_pid == -1)
	{
		const int olderrno = errno;
		close(fd);
		errno = olderrno;
		err(4, "error forking");
	}
	if(child_pid == 0)
	{
		// child
		if(write(fd, bar, 4) != 4) // fd is inherited
		{
			const int olderrno = errno;
			close(fd); // no problem that i am closing it here because fd has a reference count like links
			errno = olderrno;
			err(5, "error writing");
		}
		exit(1);
	}
	else
	{
		int child_exit_status;
		pid_t wait_status = wait(&child_exit_status);
		
		if(wait_status == -1)
		{
			const int olderrno = errno;
			close(fd);
			errno = olderrno;
			err(6, "could not wait for child process");
		}
		if(!WIFEXITED(child_exit_status))
		{
			const int olderrno = errno;
			close(fd);
			errno = olderrno;
			errx(7,"child did not terminate correctly");
		}
		if(WEXITSTATUS(child_exit_status) != 0)
		{
			const int olderrno =errno;
			close(fd);
			errno = olderrno;
			errx(8,"child did not return 0");
		}
		if(write(fd,foo+2,2) != 2)
		{
			const int olderrno = errno;
			close(fd);
			errno = olderrno;
			err(9, "could not write");
		}
	}
	printf("Elite\n");
	close(fd);
}

