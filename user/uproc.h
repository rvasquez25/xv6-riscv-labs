struct uproc {
	int pid;
	uint64 size;
	int ppid;
	uint cputime;
	char name[16];
};

struct rusage {
	uint cputime;
};
