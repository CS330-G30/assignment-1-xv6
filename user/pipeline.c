#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define NULL ((void *)0)

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		printf("Usage: %s <n> <x>\n", argv[0]);
		exit(1);
	}

	int n = atoi(argv[1]);
	int x = atoi(argv[2]);

	if (x == 0)
	{
		if (argv[2][0] == '-')
		{
			x = -1 * atoi((argv[2]) + 1);
			if (x == 0)
			{
				printf("Invalid argument\n");
				exit(1);
			}
		}
		else if (argv[2][0] != '0' || strlen(argv[2]) != 1)
		{
			printf("Invalid arguments\n");
			exit(1);
		}
	}

	if (n <= 0)
	{
		printf("n must be positive\n");
		exit(1);
	}

	int fd[2];

	if (pipe(fd) < 0)
	{
		printf("pipe failed\n");
		exit(1);
	}

	write(fd[1], &x, sizeof(x));

	// create a pipeline of n processes
	for (int i = 0; i < n; i++)
	{
		if (fork() == 0)
		{
			read(fd[0], &x, sizeof(x));

			x += getpid();
			printf("%d: %d\n", getpid(), x);

			write(fd[1], &x, sizeof(x));

			exit(0);
		}
		wait(NULL);
	}

	close(fd[0]);
	close(fd[1]);

	exit(0);
}