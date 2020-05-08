#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
	int i;

	for (i=0; i<2; i++) {
	  if (fork ())
	    fork();
	}
	printf ("%d pid: %d ppid: %d\n", i, getpid(), getppid());

	return(0);
}
