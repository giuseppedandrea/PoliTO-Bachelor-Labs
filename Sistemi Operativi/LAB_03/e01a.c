#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
	int i;

	for (i=1; i<=2; i++) {
	  if (!fork ())
	    printf ("%d pid: %d ppid: %d\n", i, getpid(), getppid());
	}
	printf ("%d pid: %d ppid: %d\n", i, getpid(), getppid());

	return(0);
}
