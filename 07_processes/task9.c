/*
    9. Да се напише програма на C, която която създава файл в текущата директория и генерира два процесa, 
    които записват низовете foo и bar в създадения файл.
    Програмата не гарантира последователното записване на низове.(Version 9.1)
    Променете програмата така, че да записва низовете последователно, като първия е foo.(Version 9.2)
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <err.h>

int main(int argc, char* argv[])
{
	int fd = open("eminem", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	//for(int i = 0; i < 1000; i++){
	if(fd == -1)
	{
		close(fd);
		err(2, "error opening file for writing");
	}
	pid_t first_process = fork();
	if(first_process == -1){
		close(fd);
		err(1, "error forking");
	}
	if(first_process == 0){ // in child
		const char* foo = "foo";
		if(write(fd, foo, strlen(foo)) != strlen(foo)){
			err(3, "error while writing");
		}
		exit(0);
	} 
	wait(NULL); // comment this line if you want to be in random line
	pid_t second_process = fork();
	if(second_process == -1)
		err(1, "error forking");
	if(second_process == 0){ // in child
		const char* bar = "bar";
		write(fd, bar, strlen(bar));
	}

	close(fd);
}

