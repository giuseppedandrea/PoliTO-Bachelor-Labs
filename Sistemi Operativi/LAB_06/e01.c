#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <ctype.h>

#define SIZE_BUF 128

void produttore(int fd[]);
void consumatore(int fd[]);

int main(int argc, char *argv[]) {
  int fd[2];

  if (pipe(fd) == -1) {
    exit(1);
  }

  if (fork() == 0) { // Produttore
    produttore(fd);
  } else {
    if (fork() == 0) { // Consumatore
      consumatore(fd);
    } else { // Padre
      while (wait((int *) 0) != -1);
    } 
  }

  return 0;
}

void produttore(int fd[]) {
  char buf[SIZE_BUF];
  int len;

  close(fd[0]);

  while (1) {
    fscanf(stdin, "%s", buf);
    
    len=strlen(buf);
    
    write(fd[1], &len, sizeof(int));

    write(fd[1], buf, len*sizeof(char));

    if (strcmp(buf, "end") == 0) {
      break;
    }
  }

  exit(0);
}

void consumatore(int fd[]) {
  char buf[SIZE_BUF];
  int i, len;

  close(fd[1]);

  while (1) {
    read(fd[0], &len, sizeof(int));

    for (i=0; i<len; i++) {
      read(fd[0], &buf[i], sizeof(char));
      buf[i]=toupper(buf[i]);
    }
    buf[i]='\0';

    fprintf(stdout, "%s\n", buf);

    if (strcmp(buf, "END") == 0) {
      break;
    }
  }

  exit(0);
}
