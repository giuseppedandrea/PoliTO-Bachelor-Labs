#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

#define PATHNAME_SIZE 4096

void lsR(char *path);

int main(int argc, char *argv[]) {
  struct stat sb;
  int length_path;

  // Verifico numero di parametri
  if (argc!=2) {
    fprintf(stdout, "Usage: %s path\n", argv[0]);
    exit(1);
  }

  // Verifico errore su entry
  if (stat(argv[1], &sb)==-1) {
    fprintf(stdout, "Errore stat per %s\n", argv[1]);
    exit(1);
  }
  // Verifico che il path sia un direttorio
  if (!S_ISDIR(sb.st_mode)) {
    fprintf(stdout, "%s non e' un direttorio\n", argv[1]);
    exit(1);
  }
  // Elimino eventuale / al termine del path
  length_path=strlen(argv[1]);
  if (argv[1][length_path-1]=='/') {
    argv[1][length_path-1]='\0';
  }

  // Chiamata a funzione ricorsiva
  lsR(argv[1]);

  exit(0);
}

void lsR(char *path) {
  DIR *dp;
  struct dirent *de;
  struct stat sb;
  char *pathname=(char *)malloc(PATHNAME_SIZE*sizeof(*pathname));

  // Apro il direttorio
  if ((dp=opendir(path))==NULL) {
    fprintf(stdout, "Errore apertura per il direttorio %s\n", path);
    return;
  }

  // Leggo il direttorio
  while ((de=readdir(dp))!=NULL) {
    sprintf(pathname, "%s/%s", path, (*de).d_name);
    fprintf(stdout, "%s\n", pathname);
    // Verifico errore su entry
    if (stat(pathname, &sb)==-1) {
      fprintf(stdout, "Errore stat per %s\n", pathname);
      continue;
    }
    // Se la entry e' un direttorio ricorro, tranne per . e ..
    if (S_ISDIR(sb.st_mode)) {
      if ((strcmp((*de).d_name, ".")) && (strcmp((*de).d_name, ".."))) {
        lsR(pathname);
      }
    }
  }

  // Chiudo il direttorio
  closedir(dp);

  return;
}
