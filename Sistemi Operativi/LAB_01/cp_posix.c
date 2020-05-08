#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 4096

int main(int argc, char *argv[]) {
  int fd_in, fd_out, n_bytes_in, n_bytes_out;
  char buffer[BUFFER_SIZE];

  if (argc!=3) {
    fprintf(stdout, "Numero parametri insufficiente!\nEsempio: nomeEseguibile fileSorgente fileDestinazione\n");
    exit(1);
  }

  if ((fd_in=open(argv[1], O_RDONLY))==-1) {
    fprintf(stdout, "Lettura del file %s non riuscita\n", argv[1]);
    exit(1);
  }

  if ((fd_out=open(argv[2], O_WRONLY | O_CREAT | O_TRUNC))==-1) {
    fprintf(stdout, "Apertura del file %s non riuscita\n", argv[2]);
    exit(1);
  }

  while ((n_bytes_in=read(fd_in, buffer, BUFFER_SIZE))>0) {
    n_bytes_out=write(fd_out, buffer, n_bytes_in);
    if (n_bytes_out==-1) {
      fprintf(stdout, "Errore nella scrittura del file %s\n", argv[2]);
      exit(1);
    }
    if (n_bytes_in!=n_bytes_out) {
      fprintf(stdout, "Errore: letti %d bytes ma scritti %d bytes\n", n_bytes_in, n_bytes_out);
    }
  }

  if (n_bytes_in==-1) {
    fprintf(stdout, "Errore nella lettura del file %s\n", argv[1]);
    exit(1);
  }

  close(fd_in);
  close(fd_out);

  exit(0);
 }
