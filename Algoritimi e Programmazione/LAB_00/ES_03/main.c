#include <stdio.h>
#include <stdlib.h>

#define MAXF 21
#define MAXM 10

void controllaFile(FILE *fp);
void riempiMatrice(FILE *fp, float matrice[][MAXM], int dim);
void elaboraMatrice(float matrice[][MAXM], int dim);
int controllaMatrice(float matrice[][MAXM], int dim);

int main(int argc, char const *argv[]) {
  FILE *fp_in;
  char nomeFile[MAXF];
  int dim;
  float matrice[MAXM][MAXM];

  printf("Inserisci nome del file da leggere: ");
  scanf("%s", nomeFile);

  fp_in=fopen(nomeFile, "r");
  controllaFile(fp_in);

  fscanf(fp_in, "%d", &dim);

  riempiMatrice(fp_in, matrice, dim);

  fclose(fp_in);

  elaboraMatrice(matrice, dim);

  if(controllaMatrice(matrice, dim))
    printf("La matrice generata dal file in ingresso e' simmetrica.\n");
  else
    printf("La matrice generata dal file in ingresso e' NON simmetrica.\n");

  return 0;
}

void controllaFile(FILE *fp) {
  if(fp==NULL) {
    printf("Errore nell'apertura del file!\n");
    exit(EXIT_FAILURE);
  }
  return;
}

void riempiMatrice(FILE *fp, float matrice[][MAXM], int dim) {
  int i, j;
  for (i = 0; i < dim; i++) {
    for (j = 0; j < dim; j++) {
      fscanf(fp, "%f", &matrice[i][j]);
    }
  }
}

void elaboraMatrice(float matrice[][MAXM], int dim) {
  int i, j;
  float k;
  for (i = 0; i < dim; i++) {
    for (j = 0; j < dim; j++) {
      if(matrice[i][j]<=0.0) {
        matrice[i][j]=0.0;
      } else {
        k=1.0;
        while(k<matrice[i][j])
          k*=10.0;
        matrice[i][j]=k;
      }
    }
  }
}

int controllaMatrice(float matrice[][MAXM], int dim) {
  int i, j;
  for (i = 0; i < dim; i++) {
    for (j = i+1; j < dim; j++) {
      if (matrice[j][i]!=matrice[i][j]) {
        return 0;
      }
    }
  }
  return 1;
}
