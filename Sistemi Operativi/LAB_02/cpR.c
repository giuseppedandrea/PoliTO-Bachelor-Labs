#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>

#define PATHNAME_SIZE 4096
#define BUFFER_SIZE 4096

void lsR(char *srcPath, char *destPath);
void cpFile(char *scrPathname, char *destPathname);

int main(int argc, char *argv[]) {
  struct stat sb;
  int length_path;

  // Verifico numero di parametri
  if (argc!=3) {
    fprintf(stdout, "Usage: %s srcPath destPath\n", argv[0]);
    exit(1);
  }

  // Verifico errore su entry sorgente
  if (stat(argv[1], &sb)==-1) {
    fprintf(stdout, "Errore stat per %s\n", argv[1]);
    exit(1);
  }
  // Verifico che il path sorgente sia un direttorio
  if (!S_ISDIR(sb.st_mode)) {
    fprintf(stdout, "%s non e' un direttorio\n", argv[1]);
    exit(1);
  }
  // Elimino eventuale / al termine del path sorgente
  length_path=strlen(argv[1]);
  if (argv[1][length_path-1]=='/') {
    argv[1][length_path-1]='\0';
  }

  // Verifico errore su entry destinazione
  if (stat(argv[2], &sb)==-1) {
    fprintf(stdout, "Errore stat per %s\n", argv[2]);
    exit(1);
  }
  // Verifico che il path destinazione sia un direttorio
  if (!S_ISDIR(sb.st_mode)) {
    fprintf(stdout, "%s non e' un direttorio\n", argv[2]);
    exit(1);
  }
  // Elimino eventuale / al termine del path destinazione
  length_path=strlen(argv[2]);
  if (argv[2][length_path-1]=='/') {
    argv[2][length_path-1]='\0';
  }

  // Chiamata a funzione ricorsiva
  lsR(argv[1], argv[2]);

  exit(0);
}

void lsR(char *srcPath, char *destPath) {
  DIR *dp;
  struct dirent *de;
  struct stat sb;
  char *scrPathname=(char *)malloc(PATHNAME_SIZE*sizeof(*scrPathname));
  char *destPathname=(char *)malloc(PATHNAME_SIZE*sizeof(*destPathname));

  // Apro il direttorio
  if ((dp=opendir(srcPath))==NULL) {
    fprintf(stdout, "Errore apertura per il direttorio %s\n", srcPath);
    return;
  }

  // Leggo il direttorio
  while ((de=readdir(dp))!=NULL) {
    sprintf(scrPathname, "%s/%s", srcPath, (*de).d_name);
    sprintf(destPathname, "%s/%s", destPath, (*de).d_name);
    fprintf(stdout, "%s %s\n", scrPathname, destPathname);
    // Verifico errore su entry
    if (stat(scrPathname, &sb)==-1) {
      fprintf(stdout, "Errore stat per %s\n", scrPathname);
      continue;
    }
    // Se la entry e' un direttorio creo direttorio nella destinazione e
    // ricorro (tranne per . e ..), altrimenti copio il file
    if (S_ISDIR(sb.st_mode)) {
      if ((strcmp((*de).d_name, ".")) && (strcmp((*de).d_name, ".."))) {
        mkdir(destPathname, S_IRUSR | S_IWUSR | S_IXUSR);
        lsR(scrPathname, destPathname);
      }
    } else {
      cpFile(scrPathname, destPathname);
    }
  }

  // Chiudo il direttorio
  closedir(dp);

  return;
}

void cpFile(char *scrPathname, char *destPathname) {
  int fd_in, fd_out, n_bytes_in, n_bytes_out;
  char buffer[BUFFER_SIZE];

  if ((fd_in=open(scrPathname, O_RDONLY))==-1) {
    fprintf(stdout, "Lettura del file %s non riuscita\n", scrPathname);
    exit(1);
  }

  if ((fd_out=open(destPathname, O_WRONLY | O_CREAT | O_TRUNC))==-1) {
    fprintf(stdout, "Apertura del file %s non riuscita\n", destPathname);
    exit(1);
  }

  while ((n_bytes_in=read(fd_in, buffer, BUFFER_SIZE))>0) {
    n_bytes_out=write(fd_out, buffer, n_bytes_in);
    if (n_bytes_out==-1) {
      fprintf(stdout, "Errore nella scrittura del file %s\n", destPathname);
      exit(1);
    }
    if (n_bytes_in!=n_bytes_out) {
      fprintf(stdout, "Errore: letti %d bytes ma scritti %d bytes\n", n_bytes_in, n_bytes_out);
    }
  }

  if (n_bytes_in==-1) {
    fprintf(stdout, "Errore nella lettura del file %s\n", scrPathname);
    exit(1);
  }

  close(fd_in);
  close(fd_out);

  return;
}
