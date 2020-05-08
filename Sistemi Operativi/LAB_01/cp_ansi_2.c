#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 4096

int main(int argc, char *argv[]) {
  FILE *fp_in, *fp_out;
  char buffer[BUFFER_SIZE];
  int n_read;

  if (argc!=3) {
    fprintf(stdout, "Numero parametri insufficiente!\nEsempio: nomeEseguibile fileSorgente fileDestinazione\n");
    exit(1);
  }

  if ((fp_in=fopen(argv[1], "r"))==NULL) {
    fprintf(stdout, "Lettura del file %s non riuscita!\n", argv[1]);
    exit(1);
  }

  if ((fp_out=fopen(argv[2], "w"))==NULL) {
    fprintf(stdout, "Lettura del file %s non riuscita!\n", argv[2]);
    exit(1);
  }

  while ((n_read=fread(buffer, sizeof(char), BUFFER_SIZE, fp_in))!=0) {
    fwrite(buffer, sizeof(char), n_read, fp_out);
  }

  fclose(fp_in);
  fclose(fp_out);

  exit(0);
 }
