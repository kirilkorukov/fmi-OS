/*
	5. Да се напише програма на C, която е аналогична на предходния пример, но принуждава процеса родител да изчака 
  	детинския си процес да завърши своето изпълнение.
*/
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <err.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#define N 200

int main(void)
{
	int status;
	if(fork() > 0){
		for(int i = 0; i < N; ++i)
			wait(&status);
			printf("parent\n");
	} else {
		for(int i = 0; i < N; ++i)
			printf("child\n");
	} exit(0);
}

