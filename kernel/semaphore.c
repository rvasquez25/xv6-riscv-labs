#include "types.h"
#include "riscv.h"
#include "param.h"
#include "defs.h"
#include "spinlock.h"

struct semtab semtable;

void
seminit(void)
{
	initlock(&semtable.lock, "semtable");
	for (int i = 0; i < NSEM; i++)
		initlock(&semtable.sem[i].lock, "sem");
}

int
semalloc()
{
	initlock(&semtable.lock, "semtable");
	for (int i = 0; i < NSEM; i++) {
		initlock(&semtable.sem[i].lock, "sem");
		if (&semtable.lock == NULL) {
			return &semtable.sem[i].lock;
		}
	}
	return -1;
}
