#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX_CHAR_FILE 20+1
#define MAX_N_CANZONI 5
#define MAX_CHAR_CANZONE 255+1

typedef struct {
  int n_canzoni;
  char canzone[MAX_N_CANZONI][MAX_CHAR_CANZONE];
} amico;

amico *letturaCanzoni(FILE *fp, int n_amici);
void generazionePlaylist(amico *brani, int n);
int principioMoltiplicazione(amico *val, char **sol, int n, int pos, int count);

int main(int argc, char const *argv[]) {
  FILE *fp_in;
  char nome_file_in[MAX_CHAR_FILE];
  int n_amici;
  amico *brani;

  printf("Inserire nome file: ");
  scanf("%s", nome_file_in);

  if ((fp_in=fopen(nome_file_in, "r"))==NULL) {
    printf("Errore nell'apertura del file\n");
    exit(EXIT_FAILURE);
  }

  fscanf(fp_in, "%d", &n_amici);

  brani=letturaCanzoni(fp_in, n_amici);

  fclose(fp_in);

  int i, j;
  for (i = 0; i < n_amici; i++) {
    printf("# %d amico\n", i);
    printf("$ %d canzoni\n", brani[i].n_canzoni);
    for (j = 0; j < brani[i].n_canzoni; j++) {
      printf("%s\n", brani[i].canzone[j]);
    }
  }

  generazionePlaylist(brani, n_amici);

  free(brani);

  return(0);
}

amico *letturaCanzoni(FILE *fp, int n_amici) {
  amico *brani;
  int i, j;

  brani=(amico *)malloc(n_amici*sizeof(*brani));

  for (i = 0; i < n_amici; i++) {
    fscanf(fp, "%d", &(brani[i].n_canzoni));

    for (j = 0; j < brani[i].n_canzoni; j++)
      fscanf(fp, "%s", brani[i].canzone[j]);
  }

  return(brani);
}

void generazionePlaylist(amico *brani, int n) {
  int i, n_playlist;
  char **sol;

  sol=(char **)malloc(n*sizeof(*sol));
  for (i = 0; i < n; i++)
    sol[i]=(char *)malloc(MAX_CHAR_CANZONE*sizeof(**sol));

  n_playlist=principioMoltiplicazione(brani, sol, n, 0, 0);

  printf("Sono state generate %d playlist\n", n_playlist);

  for (i = 0; i < n; i++)
    free(sol[i]);
  free(sol);

  return;
}

int principioMoltiplicazione(amico *val, char **sol, int n, int pos, int count) {
  int i;

  if (pos >= n) {
    printf("### Playlist %d\n", count);
    for (i = 0; i < n; i++)
      printf("%s\n", sol[i]);
    printf("\n");

    return(count+1);
  }

  for (i = 0; i < val[pos].n_canzoni; i++) {
    strcpy(sol[pos], val[pos].canzone[i]);
    count = principioMoltiplicazione(val, sol, n, pos+1, count);
  }

  return(count);
}
