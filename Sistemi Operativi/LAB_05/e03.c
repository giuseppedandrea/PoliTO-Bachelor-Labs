#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void sigUsr(int sig) {
  if (sig==SIGUSR1) {
    fprintf(stdout, "Child Woke-up\n");
  }
  if (sig==SIGUSR2) {
    fprintf(stdout, "Father Woke-up\n");
  }
}

int main (int argc, char *argv[]) {
  int pid;

  signal(SIGUSR1, sigUsr);
  signal(SIGUSR2, sigUsr);

  pid=fork();

  while (1) {
    if(pid!=0) { //padre
      sleep(1);
      kill(pid, SIGUSR1);
      pause();
    } else { //figlio
      sleep(2);
      kill(getppid(), SIGUSR2);
      pause();
    }
  }

  return 0;
}
