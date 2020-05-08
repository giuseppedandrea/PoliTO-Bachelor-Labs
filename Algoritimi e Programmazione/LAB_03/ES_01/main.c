#include <stdio.h>
#include <stdlib.h>

#define MAXF 11
#define MAXR 50

void controllaFile(FILE *fp);
void leggiMatrice(FILE *fp, int M[][MAXR], int *nr, int *nc);
int riconosciRegione(int M[][MAXR], int nr, int nc, int r, int c, int *b, int *h);

int main(int argc, char const *argv[]) {
  FILE *fp_in;
  char nomeFileIn[MAXF];
  int nr, nc, M[MAXR][MAXR], r, c, b, h, n_regione=1;

  printf("Inserisci nome del file da leggere: ");
  scanf("%s", nomeFileIn);

  fp_in=fopen(nomeFileIn, "r");
  controllaFile(fp_in);

  leggiMatrice(fp_in, M, &nr, &nc);

  fclose(fp_in);

  //Per ogni cella della matrice verifica se ci sono regioni nere e se viene individuata una regione nera stampa a schermo l'estremo superiore sinistro, la base, l'altezza e l'area
  for (r = 0; r < nr; r++) {
    for (c = 0; c < nc; c++) {
      if(riconosciRegione(M, nr, nc, r, c, &b, &h)) {
        printf("Regione %d: estr. sup. SX = <%d,%d>, b = %d, h = %d, Area = %d\n", n_regione, r, c, b, h, b*h);
        n_regione++;
      }
    }
  }

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
  fscanf(fp, "%d %d", nr, nc);
  for (i = 0; i < *nr && i < MAXR; i++)
    for (j = 0; j < *nc && i < MAXR; j++)
      fscanf(fp, "%d", &M[i][j]);
  return;
}

int riconosciRegione(int M[][MAXR], int nr, int nc, int r, int c, int *b, int *h) {
  int i, j, tmp_r, tmp_c;
  *b = 1;
  *h = 1;
  tmp_r = r;
  tmp_c = c;
  //Se la cella e' nera verifica se anche altre celle contigue sono nere (valore 1)
  if (M[r][c]) {
    //Ogni regione e' circondata da una cornice di celle bianche -> basta controllare solo il bordo superiore e sinistro (non l'intera figura)

    //Bordo superiore (base)
    //Incrementa la base partendo dalla cella successiva in quella riga finche' il colore della cella e' nero (valore 1)
    while (M[r][++tmp_c])
      (*b)++;

    //Bordo sinistro (altezza)
    //Incrementa l'altezza partendo dalla cella successiva in quella colonna finche' il colore della cella e' nero (valore 1)
    while (M[++tmp_r][c])
      (*h)++;

    //Per ogni cella della regione nera precedentemente trovata cambia il colore in bianco (valore 0)
    for (i = r; i < tmp_r; i++)
      for (j = c; j < tmp_c; j++)
        M[i][j]=0;

    return(1);
  }
  return(0);
}
