/*
	copy the content of a file to another file
	the filenames are passed as arguments
*/

#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <err.h>

int main(int argc, char* argv[])
{
	if(argc != 3){
		errx(1, "You need to parse 2 arguments %s", argv[1]);
	}

	int fd1;
	int fd2;
	char c; // read character by character

	if((fd1 = open(argv[1], O_RDONLY)) == -1){
		err(2, "Error opening file for reading");
	}
	
	if((fd2 = open(argv[2], O_CREAT | O_WRONLY, S_IRWXU | S_IRWXG | S_IRWXO)) == -1){
		close(fd1);
		err(3, "Error opening file for writing");
	}

	while(read(fd1, &c, 1) == 1){
		if(write(fd2, &c, 1) != 1){
			close(fd1); close(fd2);
			err(4, "Error writing in %s", argv[2]);
		}
	}

	close(fd1); close(fd2);


	return 42;
}

