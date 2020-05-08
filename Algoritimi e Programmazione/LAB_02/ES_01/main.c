#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXF 11
#define MAXS 51
#define MAX_DIM 10

void controllaFile(FILE *fp);
void ruotaVettore(int V[], int dir, int N, int P);
void ruotaMatrice(int M[][MAX_DIM], char r_o_c, int target, int dim1, int dim2, int P, int dir);

int main(int argc, char const *argv[]) {
  FILE *fp_in, *fp_out;
  char nomeFileIn[MAXF], nomeFileOut[MAXF], stringa[MAXS], selettore[8], direzione[9];
  int i, j, dim1, dim2, matrice[MAX_DIM][MAX_DIM], continua, num_r_o_c, posizioni;

  printf("Inserisci nome del file da leggere: ");
  scanf("%s", nomeFileIn);

  fp_in=fopen(nomeFileIn, "r");
  controllaFile(fp_in);

  printf("Inserisci nome del file da scrivere: ");
  scanf("%s", nomeFileOut);
  getchar(); //Lettura '\n'; successiva gets();

  fp_out=fopen(nomeFileOut, "w");
  controllaFile(fp_out);

  fscanf(fp_in, "%d %d", &dim1, &dim2);

  //Riempimento matrice
  for (i = 0; i < dim1 && i < MAX_DIM; i++)
    for (j = 0; j < dim2 && i < MAX_DIM; j++)
      fscanf(fp_in, "%d", &matrice[i][j]);

  fclose(fp_in);

  continua=1;
  while(continua) {
    fgets(stringa, MAXS, stdin);

    sscanf(stringa, "%s %d %s %d %*s\n", selettore, &num_r_o_c, direzione, &posizioni);

    //Selettore riga/colonna
    if (!strcmp(selettore, "riga")) {
      //Selettore sinistra/destra
      if (!strcmp(direzione, "sinistra")) {
        ruotaMatrice(matrice, 'r', num_r_o_c-1, dim1, dim2, posizioni, 0);
      } else if (!strcmp(direzione, "destra")) {
        ruotaMatrice(matrice, 'r', num_r_o_c-1, dim1, dim2, posizioni, 1);
      }
    } else if (!strcmp(selettore, "colonna")) {
      //Selettore su/giu
      if (!strcmp(direzione, "su")) {
        ruotaMatrice(matrice, 'c', num_r_o_c-1, dim1, dim2, posizioni, 0);
      } else if (!strcmp(direzione, "giu")) {
        ruotaMatrice(matrice, 'c', num_r_o_c-1, dim1, dim2, posizioni, 1);
      }
    } else if (!strcmp(selettore, "fine")) {
      continua=0;
    } else {
      printf("Selettore non valido!\n");
    }
  }

  //Stampa su file la matrice finale
  for (i = 0; i < dim1; i++) {
    for (j = 0; j < dim2; j++)
      fprintf(fp_out, "%d ", matrice[i][j]);
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

void ruotaVettore(int V[], int dir, int N, int P) {
  int i, j, tmp;
  //Numero iterazioni: numero posizioni
  for (i = 0; i < P; i++) {
    //dir==1 -> destra/giu; dir==0 -> sinistra/su
    if (dir) {
      //Copia ultima cella vettore in tmp
      tmp=V[N-1];
      //Shift a destra
      for (j = N-1; j > 0; j--)
        V[j]=V[j-1];
      //Copia tmp nella prima cella
      V[0]=tmp;
    } else {
      //Copia prima cella vettore in tmp
      tmp=V[0];
      //Shift a sinistra
      for (j = 0; j < N-1; j++)
        V[j]=V[j+1];
      //Copia tmp nell'ultima cella
      V[N-1]=tmp;
    }
  }
  return;
}

void ruotaMatrice(int M[][MAX_DIM], char r_o_c, int target, int dim1, int dim2, int P, int dir) {
  int i, vettore_col[MAX_DIM];
  if (r_o_c=='r') {
    //Richiamo funzione ruotaVettore per ruotare la riga della matrice (M[target])
    ruotaVettore(M[target], dir, dim2, P);
  } else {
    //Creazione vettore colonna con la colonna della matrice
    for (i = 0; i < dim1; i++)
      vettore_col[i]=M[i][target];
    //Richiamo funzione ruotaVettore per ruotare il vettore colonna
    ruotaVettore(vettore_col, dir, dim1, P);
    //Copia del vettore colonna nella colonna della matrice
    for (i = 0; i < dim1; i++)
      M[i][target]=vettore_col[i];
  }

  return;
}
