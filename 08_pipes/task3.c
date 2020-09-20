/*
T3 - Напишете програма на C, която демонстрира употребата на dup/dup2 между parent и child процеси. Parent-ът трябва да изпраща стринга, получен като първи аргумент на командния ред към child-а, където той да може да се чете от stdin. Child процесът да изпълняваwc -c.
*/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <err.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
	if(argc != 2)
		errx(1, "Expected 1 argument, got %d", argc - 1);

	char* our_string = argv[1];
	
	if(strlen(our_string) == 0)
	{
		printf("0\n");
		exit(0);
	}
	
	int fd[2];
	if(pipe(fd) == -1) 
		err(2, "error creating a pipe");
	pid_t childpid = fork();
	if(childpid == -1)
		err(3, "error forking");
	if(childpid == 0)
	{
		close(fd[1]);
		if(dup2(fd[0], 0) == -1)
			err(4, "cannot dup2");
		if(execl("/bin/wc", "wc", "-c", (char*)NULL) == -1)
		{
			err(5, "error executing wc");
		}
	}
	// don't need else because exec will change the whole binary
	close(fd[0]);
	write(fd[1], our_string, strlen(our_string));
	close(fd[1]);
	wait(NULL);
}

