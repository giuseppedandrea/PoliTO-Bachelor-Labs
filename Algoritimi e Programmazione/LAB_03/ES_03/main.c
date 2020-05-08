#include <stdio.h>
#include <stdlib.h>

#define MAXF 11
#define MAXR 50

void controllaFile(FILE *fp);
void leggiMatrice(FILE *fp, int M[][MAXR], int *nr, int *nc);
int verificaCammino(int M[][MAXR], int nr, int nc, int *p);

int main(int argc, char const *argv[]) {
  FILE *fp_in;
  char nomeFileIn[MAXF];
  int nr, nc, M[MAXR][MAXR], p=0;

  printf("Inserisci nome del file da leggere: ");
  scanf("%s", nomeFileIn);

  fp_in=fopen(nomeFileIn, "r");
  controllaFile(fp_in);

  //Leggi da file la matrice
  leggiMatrice(fp_in, M, &nr, &nc);

  fclose(fp_in);

  //Se il cammino e' corretto e semplice, stampa a schermo il costo del cammino...
  if (verificaCammino(M, nr, nc, &p))
    printf("Il cammino e' corretto, costa %d ed e' semplice\n", p);
  //... altrimenti stampa a schermo un errore
  else
    printf("Il cammino e' non corretto e/o non semplice\n");

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

void leggiMatrice(FILE *fp, int M[][MAXR], int *nr, int *nc) {
  int i, j;

  //Acquisizione dimensioni matrice
  fscanf(fp, "%d %d", nr, nc);

  //Per ogni cella della matrice acquisisci il "peso" della cella
  for (i = 0; i < *nr && i < MAXR; i++)
    for (j = 0; j < *nc && i < MAXR; j++)
      fscanf(fp, "%d", &M[i][j]);
  return;
}

int verificaCammino(int M[][MAXR], int nr, int nc, int *p) {
  int riga, colonna, riga_precedente, colonna_precedente, diff_riga, diff_colonna, corretto, prima_volta=1;

  while (scanf("%d %d", &riga, &colonna)==2) {
    //Se la coppia e' (-1,-1) ritorna 1 (cammino verificato) al chiamante
    if (riga==-1 && colonna==-1)
      return(1);

    //Se la cella e' gia' stata percossa ritorna 0 (cammino non verificato) al chiamante
    if (M[riga][colonna]==-1)
      return(0);

    //Se non e' la prima coppia inserita esegui il controllo...
    if (!prima_volta) {
      corretto=0;
      //Se la cella appartiene alla matrice prosegui nei controlli
      if (riga>=0 && riga<nr && colonna>=0 && colonna<nc) {
        //Calcola la differenza tra la riga/colonna precedente e la riga/colonna attuale
        diff_riga=riga-riga_precedente;
        diff_colonna=colonna-colonna_precedente;

        //Se le differenze sono comprese tra -1 e 1, la cella attuale e' in un intorno della cella precedente
        if(diff_riga>=-1 && diff_riga<=1)
          if (diff_colonna>=-1 && diff_colonna<=1)
            corretto=1;
      }
    //...altrimenti imposta il cammino corretto e resetta prima_volta
    } else {
      corretto=1;
      prima_volta=0;
    }

    //Se il cammino non e' corretto ritorna 0 (cammino non verificato) al chiamante
    if (!corretto)
      return(0);

    //Se tutti i controlli sono andati a buon fine, incrementa il "peso" del percorso e contrassegna la cella come gia' percorsa (-1). Salva la cella attuale come precedente
    (*p)+=M[riga][colonna];
    M[riga][colonna]=-1;
    riga_precedente=riga;
    colonna_precedente=colonna;
  }

  return(0);
}
