#include <stdio.h>
#include <stdlib.h>

#define MAXF 11
#define MAX_DIM 20

void controllaFile(FILE *fp);
int sommaCornice(int matrice[][MAX_DIM], int dim_max, int l, int r, int raggio, char r_o_c, int num_r_o_c);

int main(int argc, char const *argv[]) {
  FILE *fp_in, *fp_out;
  char nomeFileIn[MAXF], nomeFileOut[MAXF];
  int i, j, dim1, dim2, matrice[MAX_DIM][MAX_DIM], matriceSomma[MAX_DIM][MAX_DIM], raggio, somma;

  printf("Inserisci nome del file da leggere: ");
  scanf("%s", nomeFileIn);

  fp_in=fopen(nomeFileIn, "r");
  controllaFile(fp_in);

  printf("Inserisci nome del file da scrivere: ");
  scanf("%s", nomeFileOut);

  fp_out=fopen(nomeFileOut, "w");
  controllaFile(fp_out);

  //Acquisizione dimensioni matrice
  fscanf(fp_in, "%d %d", &dim1, &dim2);

  //Riempimento matrice
  for (i = 0; i < dim1 && i < MAX_DIM; i++)
    for (j = 0; j < dim2 && i < MAX_DIM; j++)
      fscanf(fp_in, "%d", &matrice[i][j]);

  fclose(fp_in);

  //Acquisizione raggio
  printf("Inserisci il raggio: ");
  scanf("%d", &raggio);

  //Per ogni cella della matrice calcola la somma della cornice di raggio R
  for (i = 0; i < dim1; i++) {
    for (j = 0; j < dim2; j++) {
      somma=0;

      //Somma cornice superiore (se appartiene alla matrice)
      if ((i-raggio)>=0)
        //Estremi della cornice: da SX-TOP a DX-TOP
        somma+=sommaCornice(matrice, dim2, j-raggio, j+raggio, raggio, 'r', i-raggio);

      //Somma cornice inferiore (se appartiene alla matrice)
      if ((i+raggio)<dim1)
        //Estremi della cornice: da SX-DOWN a DX-DOWN
        somma+=sommaCornice(matrice, dim2, j-raggio, j+raggio, raggio, 'r', i+raggio);

      //Somma cornice sinistra (se appartiene alla matrice)
      if ((j-raggio)>=0)
        //Estremi della cornice: da SX-(TOP+1) a SX-(DOWN-1)
        somma+=sommaCornice(matrice, dim1, i-raggio+1, i+raggio-1, raggio, 'c', j-raggio);

      //Somma cornice destra (se appartiene alla matrice)
      if ((j+raggio)<dim2)
        //Estremi della cornice: da DX-(TOP+1) a DX-(DOWN-1)
        somma+=sommaCornice(matrice, dim1, i-raggio+1, i+raggio-1, raggio, 'c', j+raggio);

      matriceSomma[i][j]=somma;
    }
  }

  //Stampa su file la nuova matrice
  fprintf(fp_out, "%d %d\n", dim1, dim2);
  for (i = 0; i < dim1; i++) {
    for (j = 0; j < dim2; j++)
      fprintf(fp_out, "%d ", matriceSomma[i][j]);
    fprintf(fp_out, "\n");
  }

  fclose(fp_out);

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

int sommaCornice(int matrice[][MAX_DIM], int dim_max, int l, int r, int raggio, char r_o_c, int num_r_o_c) {
  int i, somma=0;

  //Numero di iterazioni: da estremo 'l' a estremo 'r'
  for (i = l; i <= r; i++)
    //Se la cella appartiene alla matrice...
    if (i>=0 && i<dim_max) {
      //... se bisogna sommare una riga si fissa l'indice della riga
      if (r_o_c=='r')
        somma+=matrice[num_r_o_c][i];
      else
      //... se bisogna sommare una colonna si fissa l'indice della colonna
        somma+=matrice[i][num_r_o_c];
    }

  return(somma);
}
