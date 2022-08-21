#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		printf("Usage: %s <n> <x>\n", argv[0]);
		exit(1);
	}

	int n = atoi(argv[1]);
	int x = atoi(argv[2]);
	int p = 0;

	if (n <= 0)
	{
		printf("n must be positive\n");
		exit(1);
	}

	// make FILE_NAME a global variable
	char *FILE_NAME = "pipeline.txt";

	// clear the file
	int fd = open(FILE_NAME, 514);
	write(fd, &p, sizeof(int));
	close(fd);

	// create a pipeline of n processes
	for (int i = 0; i < n; i++)
	{
		if (fork() == 0)
		{
			fd = open(FILE_NAME, 2);
			read(fd, &x, sizeof(int));
			close(fd);

			x += getpid();
			printf("%d: %d \n", getpid(), x);

			// overwrite the file with the new value
			fd = open(FILE_NAME, 2);
			write(fd, &x, sizeof(int));
			close(fd);

			exit(0);
		}
		wait(&p);
	}
	exit(0);
}