#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main() {
	printf("System is up from %d seconds\n", uptime());
	exit(0);
}
