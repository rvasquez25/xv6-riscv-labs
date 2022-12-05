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
semalloc(void)
{
	acquire(&semtable.lock);
	for (int i = 0; i < NSEM; i++) {
		if(semtable.sem[i].valid==0) {
			semtable.sem[i].valid=1;
			release(&semtable.lock);
			//return index of unused location
			return i;
		}
	}
	release(&semtable.lock);
	//else return -1
	return -1;
}

int 
semdealloc(int index)
{
	acquire(&semtable.lock);
	//invalidate entry in sem table
	semtable.sem[index].valid = 0;
	release(&semtable.lock);
	return 0;
}
