/*
    7. Да се напише програма на С, която получава като параметри три команди (без параметри), 
    изпълнява ги последователно, като изчаква края на всяка и извежда на стандартния изход 
    номера на завършилия процес, както и неговия код на завършване.
*/
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <err.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char* argv)
{
	const int NUMBER_COMMANDS = 3;
	if(argc != NUMBER_COMMANDS + 1)
		errx(1, "Expected %d arguments, got %d", NUMBER_COMMANDS, argc - 1);

	for(int i = 1; i < argc; i++)
	{
		pid_t child_process = fork();
		if(child_process == -1)
			err(2, "error forking");
		if(child_process == 0)
		{
			/*char buf[256];
			int nfn_size = sprintf("/bin/%s", argv[i]);
			char* fullcommand = malloc(nfn_size + 1);
			memcpy(fullcommand, buf, nfn_size);
			if(execl(fullcommand, "my_command",(char*)NULL) == -1)
				err(3, "error executing %s", argv[i]);
			free(fullcommand);
			*/exit(0);
		}
		else
		{
			int child_exit_status;
			if(wait(&child_exit_status) == -1)
				err(4, "error while waiting");
			//if(!WIFEXITED(child_exit_status) || WEXITSTATUS(child_exit_status) != 0)
			//	err(5, "child did not terminate normally");
			printf("%s command\n",argv[i]);
		}
	}
}

