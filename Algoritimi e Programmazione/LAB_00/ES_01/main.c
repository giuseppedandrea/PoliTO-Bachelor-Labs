#include <stdio.h>
#include <stdlib.h>

#define MAXF 11

void controllaFile(FILE *fp);

int main(int argc, char const *argv[]) {
  FILE *fp;
  char nomeFile[MAXF];
  float x, y, z, sommaX, sommaY, sommaZ;
  int n;

  printf("Inserisci nome del file da leggere: ");
  scanf("%s", nomeFile);

  fp=fopen(nomeFile, "r");
  controllaFile(fp);

  n=0;
  sommaX=0;
  sommaY=0;
  sommaZ=0;
  while(fscanf(fp, "%f %f %f", &x, &y, &z)==3)
  {
    sommaX+=x;
    sommaY+=y;
    sommaZ+=z;
    n++;
  }

  fclose(fp);

  printf("Baricentro: %.1f %.1f %.1f\n", sommaX/n, sommaY/n, sommaZ/n);

  return 0;
}

void controllaFile(FILE *fp)
{
  if(fp==NULL)
  {
    printf("Errore nell'apertura del file!\n");
    exit(EXIT_FAILURE);
  }
  return;
}
