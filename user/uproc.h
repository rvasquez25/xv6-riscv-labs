enum uprocstate { UNUSED, USED, SLEEPING, RUNNABLE, RUNNING };

struct uproc {
	int pid;
	enum uprocstate state;
	uint64 size;
	int ppid;
	uint cputime;
	char name[16];
};
