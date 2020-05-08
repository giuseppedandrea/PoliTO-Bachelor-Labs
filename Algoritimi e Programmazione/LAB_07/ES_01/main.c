#include <stdio.h>
#include <stdlib.h>

#define MAXN 20
#define MAXU 10

void setCover(int S[][10], int n, int k);
int combinazioniSemplici(int S[][MAXU], int *sol, int n, int k, int start, int pos);
int controlloSoluzione(int S[][MAXU], int *sol, int k);
void stampaSoluzione(int *sol, int k);

int main(int argc, char const *argv[]) {
  int S[MAXN][MAXU], n, k, i, j;

  printf("Numero sottoinsiemi: ");
  scanf("%d", &n);

  for (i = 0; i < n; i++) {
    printf("- Sottoinsieme %d\n", i);
    for (j = 0; ; j++) {
      printf("-- Elemento %d: ", j);
      scanf("%d", &S[i][j]);
      if (S[i][j]==0)
        break;
    }
  }

  printf("Inserire numero collezione k di sottoinsiemi: ");
  scanf("%d", &k);

  setCover(S, n, k);

  return(0);
}

void setCover(int S[][MAXU], int n, int k) {
  int *sol;

  sol=(int *)malloc(k*sizeof(*sol));

  if (combinazioniSemplici(S, sol, n, k, 0, 0))
    stampaSoluzione(sol, k);
  else
    printf("Non esiste nessuna collezione di %d sottoinsiemi la cui unione sia U\n", k);

  free(sol);

  return;
}

int combinazioniSemplici(int S[][MAXU], int *sol, int n, int k, int start, int pos) {
  int i;

  if (pos >= k)
    return(controlloSoluzione(S, sol, k));

  for (i = start; i < n; i++) {
    sol[pos]=i;

    if (combinazioniSemplici(S, sol, n, k, i+1, pos+1))
      return(1);
  }

  return(0);
}

int controlloSoluzione(int S[][MAXU], int *sol, int k) {
  int i, j, mark[(MAXU-1)];

  for (i = 0; i < (MAXU-1); i++)
    mark[i]=0;

  for (i = 0; i < k; i++)
    for (j = 0; S[sol[i]][j]!=0 ; j++)
      mark[(S[sol[i]][j])-1]++;

  for (i = 0; i < (MAXU-1); i++)
    if (mark[i]!=1)
      break;

  if (i==(MAXU-1))
    return(1);

  return(0);
}

void stampaSoluzione(int *sol, int k) {
  int i;

  printf("Collezione di %d sottoinsiemi la cui unione sia U:\n", k);
  for (i = 0; i < k; i++)
    printf("S%d\n", sol[i]);

  return;
}
