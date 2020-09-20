/*
T2 - Напишете програма на C, която демонстрира комуникация през pipe между parent и child процеси. Parent-ът трябва да изпраща стринга, получен като първи аргумент на командния ред към child-а, който да го отпечатва на стандартния изход.
*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
	if(argc != 2)
		errx(1, "Expected 1 argument got %d", argc - 1);
	
	char* string = argv[1];
	
	int pipefd[2];
	if(pipe(pipefd) == -1)
		err(2, "could not create pipe");

	pid_t child_pid = fork();
	if(child_pid == -1)
		err(3, "error forking");
	if(child_pid == 0)
	{
		close(pipefd[1]);
		char buf;
		while(read(pipefd[0], &buf, 1) == 1)
		{
			write(1, &buf, 1);
		}
	}	
	else
	{
		close(pipefd[0]);
		write(pipefd[1], string, strlen(string));
		close(pipefd[1]);
		wait(NULL); 
	}
	write(1,'\n',1);
}

