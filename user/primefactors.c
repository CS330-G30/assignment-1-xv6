#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
	int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};

	if (argc != 2)
	{
		printf("Usage: %s <n>\n", argv[0]);
		exit(1);
	}

	int n = atoi(argv[1]);

	if (n < 2 || n > 100)
	{
		printf("Invalid argument\n");
		exit(1);
	}

	int fd[2];
	if (pipe(fd) < 0)
	{
		printf("pipe failed\n");
		exit(1);
	}

	write(fd[1], &n, sizeof(n));

	for (int i = 0; i < 25; i++)
	{
		int t;

		if (fork() == 0)
		{
			read(fd[0], &t, sizeof(t));

			if (t % primes[i] == 0)
			{
				while (t % primes[i] == 0)
				{
					printf("%d, ", primes[i]);
					t /= primes[i];
				}

				printf("[%d]\n", getpid());
			}

			write(fd[1], &t, sizeof(t));

			exit(0);
		}
		wait(0);
	}
	exit(0);
}
