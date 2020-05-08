#include <stdio.h>
#include <stdlib.h>

#define MAXF 11
#define N 20

void controllaFile(FILE *fp);

int main(int argc, char const *argv[]) {
  FILE *fp;
  char nomeFile[MAXF];
  int i, j, n, matrice[N][N];

  printf("Inserisci nome del file da leggere: ");
  scanf("%s", nomeFile);

  fp=fopen(nomeFile, "r");
  controllaFile(fp);

  //Riempimento matrice
  fscanf(fp, "%d", &n);
  for (i = 0; i < n && i < N; i++)
    for (j = 0; j < n && i < N; j++)
      fscanf(fp, "%d", &matrice[i][j]);

  fclose(fp);

  //Visualizzazione contenuto della matrice a spirale
  //Numero di iterazione (spirali): se n righe/colonne e' pari -> n/2; se n righe/colonne e' dispari -> (n/2)+1
  for (i = 0; i < ((n%2) ? ((n/2)+1) : (n/2)) ; i++) {
    //Riga superiore (da SX a DX)
    for (j = i; j < (n-i); j++)
      printf("%d ", matrice[i][j]);
    //Colonna destra (da TOP+1 a DOWN)
    for (j = i+1; j < (n-i); j++)
      printf("%d ", matrice[j][n-i-1]);
    //Riga inferiore (da DX-1 a SX)
    for (j = n-i-2; j >= i; j--)
      printf("%d ", matrice[n-i-1][j]);
    //Colonna sinistra (da DOWN-1 a TOP)
    for (j = n-i-2; j > i; j--)
      printf("%d ", matrice[j][i]);
  }
  printf("\n");

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
