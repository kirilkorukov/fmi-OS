/*
    6. Да се напише програма на С, която получава като параметър команда (без параметри) 
    и при успешното ѝ изпълнение, извежда на стандартния изход името на командата.
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <err.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		errx(1, "Usage: %s <command>", argv[0]);
	}
	
	// turn argv[1] into /bin/argv[1]
	char* buffer[256];
	int nfn_size = sprintf(buffer, "/bin/%s", argv[1]);
	char* dest = malloc(nfn_size + 1); // for \0
	memcpy(dest, buffer, nfn_size);

	printf("%s\n", dest);

	const char* cmd = argv[1];

	pid_t child_pid = fork();

	if(child_pid < 0)	
	{
		err(2, "error forking");
	}
	else if(child_pid == 0)
	{
		// child
		if(execlp(dest, "our_command", (char*)NULL) == -1)
		{
			err(3, "error executing %s", cmd);
		}
	}
	else
	{
		// parent
		int child_exit_status;
		if(wait(&child_exit_status) == -1)
		{
			err(4, "error waiting for child");
		}
		if(!WIFEXITED(child_exit_status))
		{
			errx(5, "child process did not terminate normally");
		}
		if(WEXITSTATUS(child_exit_status) != 0)
			errx(6, "child exit code not 0");
	}

	printf("%s\n", cmd);
	free(dest);
}

