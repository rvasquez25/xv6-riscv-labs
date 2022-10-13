#include "kernel/param.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/uproc.h"
#include "user/user.h"
#define MAXARGS 16

int main(int argc, char *argv[])
{
	char *newargv[MAXARGS];
	struct rusage ru;

	if (argc < 2) 
	{
		printf("Usage: time <comm> [args...]");
		exit(-1);
	}

	//set up the arguments
	for(int i=0; i<argc; i++)
	{
		newargv[i] = argv[i+1];
	}
	newargv[argc-1] = 0;

	int start = uptime();
	int rc = fork();
	if (rc ==0)
		exec(newargv[0], newargv);
	wait2(0, &ru); //parent
	int elapsed = uptime() - start;
	printf("elapsed time: %d ticks, cpu time: %d ticks, %d% CPU\n", elapsed, ru.cputime, ru.cputime*100/elapsed);
	exit(0);
}
