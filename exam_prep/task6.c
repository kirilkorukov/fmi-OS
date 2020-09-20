//Реализирайте команда cat, работеща с произволен брой подадени входни параметри.

#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <errno.h>
#include <err.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	
for(int i = 1; i < argc; i++){
	int fd;
	if((fd = open(argv[i], O_RDONLY)) == -1){
		printf("%s err", argv[i]);
		continue;
	}
	struct stat st;
	if(stat(argv[i], &st) == -1){
		close(fd);
		printf("%s err", argv[i]);
		continue;
	}
	void* buf = malloc(st.st_size);
	if(read(fd, buf, st.st_size) != st.st_size)
	{
		printf("%s error", argv[i]);
		free(buf);
		close(fd);
		continue;
	}
	write(1, buf, st.st_size);
	close(fd);
	free(buf);
}

exit(1);
}

