//Реализирайте команда cp, работеща с произволен брой подадени входни параметри.
// task7 from to to1 to2

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>

void copyFile(int fd, const char* path) // Relies that fd is already opened, i can open it here,too but it is faster this way
{
	int fd_w = open(path, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if(fd_w == -1)
	{
		err(1, "error opening %s", path);	
	}

	char buf[1024];
	ssize_t read_size;	
	while((read_size = read(fd, &buf, sizeof(buf))) > 0)
	{
		if(write(fd_w, &buf, read_size) != read_size)
		{
			const int olderrno = errno;
			close(fd_w);
			errno = olderrno;			
			err(2, "error writing at %s", path);
		}
	}

	close(fd_w);
}


int main(int argc, char* argv[])
{
	if(argc < 3)
	{
		errx(5, "We need at least 2 arguments");
	}
	int fd = open(argv[1], O_RDONLY);
	if(fd == -1)
	{
		err(6, "error opening %s", argv[1]);
	}

	for(int i = 2; i < argc; i++)
	{
		// if it is a file just copy it's content
		// if it's a dir i should change the path a little bit

		struct stat st;
		if((stat(argv[i], &st) == -1) || (S_ISREG(st.st_mode)))
		{
			// file is a regular file or does not exist so pass only the path to our function
			copyFile(fd, argv[i]);
		}
		else if(S_ISDIR(st.st_mode))
		{
			char dest_buf[256];
			int nfn_size = sprintf(dest_buf, "%s/%s", argv[i], argv[1]);
			char* dest_name = malloc(nfn_size + 1); // + 1 for \0
			memcpy(dest_name, dest_buf, nfn_size);
			copyFile(fd, dest_name);
			free(dest_name);
		}
		else
		{
			warnx("File %s is not a valid file", argv[i]);
		}
	}

	close(fd);
	exit(0);
}

