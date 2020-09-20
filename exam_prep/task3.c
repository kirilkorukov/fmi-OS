
// Реализирайте команда wc, с един аргумент подаден като входен параметър
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <err.h>
#include <errno.h>

int main(int argc, char* argv[])
{
	if(argc != 2){
		errx(1, "Usage: %s <filename>", argv[0]);
	}

	int symbols = 0, words = 0, lines = 0;
	
	int fd;
	if((fd = open(argv[1], O_RDONLY)) == -1){
		err(2, "Error opening %s for reading", argv[1]);
	}

	char c;

	while(1){
		int bytes = read(fd, &c, 1);

		if(bytes == 0) break; // end of file
		if(bytes == -1)
		{
			const int olderrno = errno;
			close(fd);
			errno = olderrno;
			err(3, "Error reading from %s", argv[1]);
		}
		symbols++;
		if(c == ' ') words++;
		else if(c == '\n'){
			lines++;
			words++;
		}
	}

	printf("%d %d %d %s \n", lines, words, symbols, argv[1]);
	
	close(fd);

	return 42;
}

