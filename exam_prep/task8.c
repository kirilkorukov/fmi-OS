//Koпирайте файл /etc/passwd в текущата ви работна директория и променете разделителят на копирания файл от ":", на "?"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <err.h>
#include <errno.h>

int main(int argc, char* argv[])
{
int fd;
if((fd = open("my_passwd", O_RDONLY)) == -1){
	err(1, "error opening my_passwd");
}

int fd2;
if((fd2 = open("eminem/my_passwd", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU)) == -1)
{
	const int olderrno = errno;
	close(fd);
	errno = olderrno;
	err(2, "error opening eminem");
}

char c;
while(1)
{
	int read_size = read(fd, &c, 1);
	if(read_size == 0) break;
	else if(read_size == -1)
	{
		const int olderrno = errno;
		close(fd); close(fd2);
		errno = olderrno;
		err(3, "error reading");
	}
	if(c == ':') c = '?';
	int write_size = write(fd2, &c, 1);
	if(write_size == -1)
	{
		const int olderrno = errno;
		close(fd); close(fd2);
		errno = olderrno;
		err(4, "error writing");
	}
}
close(fd);
close(fd2);
exit(1);
}

