#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main (int argc, char *argv[]) {
  int fd, n, i, j, val;

  if (argc!=2) {
    fprintf(stderr, "Usage: %s <inFile>\n", argv[0]);
    exit(1);
  }

  if ((fd=open(argv[1], O_RDWR))==-1) {
    fprintf(stderr, "Errore apertura file %s\n", argv[1]);
    exit(1);
  }

  if(read(fd, &n, sizeof(int))==-1) {
    fprintf(stderr, "Errore lettura file %s\n", argv[1]);
    exit(1);
  }

  fprintf(stdout, "n=%d\n", n);

  lseek(fd, sizeof(int), SEEK_SET);
  fprintf(stdout, "Vettore non ordinato:\t");
  for (i=0; i<n; i++) {
    read(fd, &val, sizeof(int));
    fprintf(stdout, "%d ", val);
  }
  fprintf(stdout, "\n");


  for (i=0; i<(n-1); i++) {
    for (j=0; j<(n-1-i); j++) {
      if (fork()) { //padre
        wait((int *) 0);
      } else { // figlio
        int val1, val2, tmp;
        lseek(fd, (j+1)*sizeof(int), SEEK_SET);
        read(fd, &val1, sizeof(int));
        read(fd, &val2, sizeof(int));
        if (val1>val2) {
          tmp=val1;
          val1=val2;
          val2=tmp;
          lseek(fd, (j+1)*sizeof(int), SEEK_SET);
          write(fd, &val1, sizeof(int));
          write(fd, &val2, sizeof(int));
        }
        exit(0);
      }
    }
  }

  lseek(fd, sizeof(int), SEEK_SET);
  fprintf(stdout, "Vettore ordinato:\t");
  for (i=0; i<n; i++) {
    read(fd, &val, sizeof(int));
    fprintf(stdout, "%d ", val);
  }
  fprintf(stdout, "\n");

  close(fd);

  return 0;
 }
