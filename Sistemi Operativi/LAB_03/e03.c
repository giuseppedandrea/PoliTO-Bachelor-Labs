#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
  pid_t pid1, pid2;

  printf("P1 pid=%d ppid=%d\n", getpid(), getppid());

  pid1=fork();
  if (pid1) { // (P2457)
    sleep(3);
    printf("P2 pid=%d ppid=%d\n", getpid(), getppid());
    pid2=fork();
    if (pid2) {
      sleep(3);
      printf("P4 pid=%d ppid=%d\n", getpid(), getppid());
      waitpid(pid2, (int *) 0, 0);	    
    } else {
      sleep(15);
      printf("P5 pid=%d ppid=%d\n", getpid(), getppid());
      exit(0);
    }
    sleep(3);
    printf("P7 pid=%d ppid=%d\n", getpid(), getppid());
    waitpid(pid1, (int *) 0, 0);
  } else { // (P368)
    sleep(3);
    printf("P3 pid=%d ppid=%d\n", getpid(), getppid());
    if (fork()) {
      wait((int *) 0);    
    } else {
      sleep(3);
      printf("P6 pid=%d ppid=%d\n", getpid(), getppid());
      exit(0);
    }
    sleep(3);
    printf("P8 pid=%d ppid=%d\n", getpid(), getppid());
    exit(0);
  }

  sleep(3);
  printf("P9 pid=%d ppid=%d\n", getpid(), getppid());

  return(0);
  }
