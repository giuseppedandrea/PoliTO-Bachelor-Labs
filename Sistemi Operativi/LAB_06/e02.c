#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

void padre (int fd1[], int fd2[], pid_t pid_figlio);
void figlio (int fd1[], int fd2[], pid_t pid_padre);

int main (int argc, char *argv[]) {
  int fd1[2], fd2[2];
  pid_t pid_figlio;

  if (pipe(fd1) == -1) {
    exit(1);
  }

  if (pipe(fd2) == -1) {
    exit(1);
  }

  setbuf(stdout, 0);

  pid_figlio=fork();
  if (pid_figlio) {
    padre(fd1, fd2, pid_figlio);
  } else {
    figlio(fd1, fd2, getppid());
  }  

  return 0;
}

void padre (int fd1[], int fd2[], pid_t pid_figlio) {
  pid_t pid;
  
  close(fd1[0]);
  close(fd2[1]);

  while (1) {
    pid=getpid();

    sleep(1);

    fprintf(stdout, "I'm the father (PID=%d)\n", pid);
  
    write(fd1[1], &pid, sizeof(int));
    
    read(fd2[0], &pid, sizeof(int));    
  }
}

void figlio (int fd1[], int fd2[], pid_t pid_padre) {
  pid_t pid;

  close(fd1[1]);
  close(fd2[0]);

  while (1) {
    read(fd1[0], &pid, sizeof(int));

    pid=getpid();

    sleep(1);

    fprintf(stdout, "I'm the child (PID=%d)\n", pid);

    write(fd2[1], &pid, sizeof(int));
  }
}
