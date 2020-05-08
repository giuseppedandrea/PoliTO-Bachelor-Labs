#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  FILE *fp_in, *fp_out;
  char buffer;

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

  while ((buffer=fgetc(fp_in))!=EOF) {
    fputc(buffer, fp_out);
  }

  fclose(fp_in);
  fclose(fp_out);

  exit(0);
 }
