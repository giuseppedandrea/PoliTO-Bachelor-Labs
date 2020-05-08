#include <stdio.h>
#include <stdlib.h>

#define MAXC_FILE 10

void mallocMatrice(int ***matr, int nr, int nc);
void leggiMatrice(FILE *fp, int **matr, int nr, int nc);
void freeMatrice(int **matr, int nr);
void elaboraContenuti(int **matr, int ***diagonali, int *lunghezze, int nr, int nc, int tipo_diagonale);
void stampaContenuti(int ***vett_vett, int n_diagonali, int *lunghezze, int tipo_diagonale);

int main(int argc, char const *argv[]) {
  FILE *fp_in;
  char nome_file_in[MAXC_FILE+1];
  int nr, nc;
  int **matr, **diagonali, **anti_diagonali, *lunghezze;

  //Inserimento nome file
  printf("Inserire nome file da leggere: ");
  scanf("%s", nome_file_in);

  //Apertura file
  if ((fp_in=fopen(nome_file_in, "r"))==NULL) {
    printf("Errore nell'apertura del file!\n");
    return(EXIT_FAILURE);
  }

  //Lettura numero righe/colonne
  fscanf(fp_in, "%d %d", &nr, &nc);

  //Alloca matrice dinamicamente
  mallocMatrice(&matr, nr, nc);

  //Leggi valori matrice da file
  leggiMatrice(fp_in, matr, nr, nc);

  fclose(fp_in);

  //Vettore dinamico contenente lunghezze delle diagonali/anti-diagonali
  lunghezze=(int *)malloc((nr+nc-1)*sizeof(int *));

  //Genera vettori di vettori per diagonali/anti_diagonali
  elaboraContenuti(matr, &diagonali, lunghezze, nr, nc, 0);

  elaboraContenuti(matr, &anti_diagonali, lunghezze, nr, nc, 1);

  //Libera memoria dinamica
  freeMatrice(matr, nr);

  //Stampa diagonali
  printf("Diagonali:\n");
  stampaContenuti(&diagonali, nr+nc-1, lunghezze, 0);

  //Stampa anti-diagonali
  printf("Anti-diagonali:\n");
  stampaContenuti(&anti_diagonali, nr+nc-1. , lunghezze, 1);

  return 0;
}

void mallocMatrice(int ***matr, int nr, int nc) {
  int i;

  (*matr)=(int **)malloc(nr*sizeof(int *));
  for (i = 0; i < nr; i++)
    (*matr)[i]=(int *)malloc(nc*sizeof(int));

  return;
}

void leggiMatrice(FILE *fp, int **matr, int nr, int nc) {
  int i, j;

  for (i = 0; i < nr; i++)
    for (j = 0; j < nc; j++)
      fscanf(fp, "%d", &matr[i][j]);

  return;
}

void elaboraContenuti(int **matr, int ***diagonali, int *lunghezze, int nr, int nc, int tipo_diagonale) {
  int i, j, n_diagonali=nr+nc-1, lunghezza_diagonale, indice_riga, indice_colonna;

  (*diagonali)=(int **)malloc(n_diagonali*sizeof(int *));

  lunghezza_diagonale=0;
  for (i = 0; i < n_diagonali; i++) {
    //Diagonali nascenti nella prima riga (tipo_diagonale==0)/ultima riga (tipo_diagonale==1)
    //Scorrimento colonne: da destra (ultima colonna) verso sinistra
    if ((nc-1-i)>=0) {
      if (nr==nc || i<((nc>nr)?nr:nc))
        lunghezza_diagonale++;
      if (!tipo_diagonale)
        indice_riga=0;
      else
        indice_riga=nr-1;
      indice_colonna=nc-1-i;
    //Diagonali nascenti nella prima colonna, esclusa la prima (tipo_diagonale==0)/ultima (tipo_diagonale==1) cella
    //Scorrimento righe: dall'alto verso il basso (tipo_diagonale==0)/ dal basso verso l'alto (tipo_diagonale==1)
    } else {
      if (nr==nc || i>((nc>nr)?nr:nc))
        lunghezza_diagonale--;
      if (!tipo_diagonale)
        indice_riga=i-nc+1;
      else
        indice_riga=n_diagonali-1-i;
      indice_colonna=0;
    }

    //Salvataggio lunghezza diagonale/anti-diagonali
    lunghezze[i]=lunghezza_diagonale;

    //Creazione vettore diagonali/anti-diagonali
    (*diagonali)[i]=(int *)malloc(lunghezza_diagonale*sizeof(int));

    //Riempimento vettore diagonali/anti-diagonali
    for (j = 0; j < lunghezza_diagonale; j++)
      //Tipo diagonale 0: per diagonali
      //Tipo diagonale 1: per anti-diagonali
      if (!tipo_diagonale)
        (*diagonali)[i][j]=matr[indice_riga++][indice_colonna++];
      else
        (*diagonali)[i][j]=matr[indice_riga--][indice_colonna++];
  }

  return;
}

void freeMatrice(int **matr, int nr) {
  int i;

  for (i = 0; i < nr; i++)
    free(matr[i]);
  free(matr);

  return;
}

void stampaContenuti(int ***vett_vett, int n_diagonali, int *lunghezze, int tipo_diagonale) {
  int i, j;

  //Tipo diagonale 0: per diagonali
  //Tipo diagonale 1: per anti-diagonali
  if (!tipo_diagonale)
    for (i = 0; i < n_diagonali; i++) {
      for (j = 0; j < lunghezze[i]; j++)
        printf("%d ", (*vett_vett)[i][j]);
      printf("\n");
    }
  else
    for (i = n_diagonali-1; i >= 0; i--) {
      for (j = 0; j < lunghezze[i]; j++)
        printf("%d ", (*vett_vett)[i][j]);
      printf("\n");
    }

  return;
}
