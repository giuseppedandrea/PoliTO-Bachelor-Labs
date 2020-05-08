#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int i, j, n, t;
  pid_t pid;

  if (argc != 3) {
    printf("Usage: %s <n> <t>\n", argv[0]);
    return(1);
  }

  n=atoi(argv[1]);
  t=atoi(argv[2]);

  for (i=0; i<n; i++) {
    pid=getpid();
    for (j=0; j<2; j++) {
      if (! fork())
        break;
    }
    if (pid == getpid())
      exit(0);
  }

  sleep(t);

  printf("pid=%d ppid=%d\n", getpid(), getppid());

  return(0);
  }
