//Реализирайте команда cp, работеща с два аргумента, подадени като входни параметри.

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include <errno.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
	if(argc != 3)
	{
		errx(1, "Usage: %s <from> <to>", argv[0]);
	}	
	
	int fd1;
	if((fd1 = open(argv[1], O_RDONLY)) == -1)
	{
		err(2, "Error opening %s for reading", argv[1]);
	}
	int fd2;
	if((fd2 = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR)) == -1){
		const int olderrno = errno;
		close(fd1);
		err(3, "Error opening %s for writing", argv[2]);
	}
	struct stat st;
	if(stat(argv[1], &st) == -1)
	{
		const int olderrno = errno;
		close(fd1); close(fd2); 
		errno = olderrno;
		err(4, "Error with stat");
	}

	void* buf = malloc(st.st_size);
	if(read(fd1, buf, st.st_size) != st.st_size)
	{	
		const int olderrno = errno;
		close(fd1); close(fd2);
		errno = olderrno;
		err(5, "error reading");
	}
	if(write(fd2, buf, st.st_size) != st.st_size)
	{
		const int olderrno = errno;
		close(fd1); close(fd2);
		errno = olderrno;
		err(6, "error writing");
	}
	close(fd1);
	close(fd2);
	free(buf);

	exit(1);
}

