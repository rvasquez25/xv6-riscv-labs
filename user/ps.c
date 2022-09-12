/*
 *  Skeleton code for ps.c
 */
#include "kernel/param.h"
#include "kernel/types.h"
#include "user/uproc.h"
#include "user/user.h"

int
main(int argc, char **argv)
{
	
	struct uproc uproc[NPROC];
	int nprocs;

	struct uproc *p;
	static char *states[] = {
		[UNUSED]	"unused",
		[SLEEPING]	"sleep ",
		[RUNNABLE]	"runble",
		[RUNNING]	"run   ",
		[ZOMBIE]	"zombie",
	};

	nprocs = getprocs(uproc);
	if (nprocs < 0)
		exit(-1);

	printf("pid\tstate\tsize\tppid\tname\n");
	for(p = uproc; p < &uproc[nprocs]; p++) {
		printf("%d\t%s\t%d\t%d\t%s\n", p->pid, states[p->state], p->size, p->ppid, p->name);
	}
	exit(0);
}
