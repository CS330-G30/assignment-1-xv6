#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define NULL ((void *)0)

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		printf("Usage: %s <m> <n>\n", argv[0]);
		exit(1);
	}

	int m = atoi(argv[1]);
	int n = atoi(argv[2]);

	if (m <= 0)
	{
		printf("Invalid arguments\n");
		exit(1);
	}

	if (n != 0 && n != 1)
	{
		printf("Invalid arguments\n");
		exit(1);
	}

	if ((n == 0 && argv[2][0] != '0') || (m == 0 && argv[1][0] != '0'))
	{
		printf("Invalid arguments\n");
		exit(1);
	}

	if (fork() == 0)
	{
		if (n == 0)
		{
			sleep(m);
		}
		printf("%d: Child.\n", getpid());
		exit(0);
	}
	else
	{
		if (n == 1)
		{
			sleep(m);
		}
		printf("%d: Parent.\n", getpid());
		wait(NULL);
		exit(0);
	}
}