#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int max_scambi=INT_MAX;

int *initSeq(int *N);
void elaboraSeq(int *seq, int N);
void disposizioniRipetute(int *seq, int *val, int *sol, int *fin, int n, int k, int pos);
int promising(int *seq, int *sol, int N, int pos);
void controlloSoluzione(int *seq, int *sol, int *fin, int N);
void stampaSol(int *sol, int N);

int main(int argc, char const *argv[]) {
  int N, *seq;

  seq=initSeq(&N);

  elaboraSeq(seq, N);

  free(seq);

  return(0);
}

int *initSeq(int *N) {
  int i, *seq;

  scanf("%d", &(*N));

  seq=(int *)malloc((*N)*sizeof(*seq));

  for (i = 0; i < *N; i++)
    scanf("%d", &seq[i]);

  return(seq);
}

void elaboraSeq(int *seq, int N) {
  int i, *val, *sol, *fin;

  val=(int *)malloc(2*sizeof(*val));
  val[0]=0;
  val[1]=1;

  sol=(int *)malloc(N*sizeof(*sol));
  fin=(int *)malloc(N*sizeof(*fin));
  for (i = 0; i < N; i++)
    sol[i]=fin[i]=0;

  disposizioniRipetute(seq, val, sol, fin, 2, N, 0);

  stampaSol(fin, N);

  free(val);
  free(sol);
  free(fin);

  return;
}

void disposizioniRipetute(int *seq, int *val, int *sol, int *fin, int n, int N, int pos) {
  int i;

  if (pos>=N) {
    controlloSoluzione(seq, sol, fin, N);
    return;
  }

  for (i = 0; i < n; i++) {
    sol[pos]=val[i];

    if (promising(seq, sol, N, pos))
      disposizioniRipetute(seq, val, sol, fin, n, N, pos+1);
  }

  return;
}

int promising(int *seq, int *sol, int N, int pos) {
  // Pruning: le frecce agli estremi devono puntare solo verso l'interno
  if (pos==0)
    if (seq[0]==!sol[0])
      return(0);

  if (pos==(N-1))
    if (seq[N-1]==sol[N-1])
      return(0);

  return(1);
}

void controlloSoluzione(int *seq, int *sol, int *fin, int N) {
  int i, *ris, num_scambi=0, sinistra=0, destra=0;

  ris=(int *)malloc(N*sizeof(*ris));

  for (i = 0; i < N; i++) {
    if (sol[i]==1) {
      ris[i]=!seq[i];
      num_scambi++;
    }
    else {
      ris[i]=seq[i];
    }
  }

  // Se l'insieme non ha cardinalita' minire di quello attuale, return
  if (num_scambi>=max_scambi)
    return;

  //ris[0]=0 && ris[N-1]=1 => a sinistra gli 0; a destra gli 1
  i=0;
  while (i<N) {
    while (ris[i]==0 && i<N) {
      sinistra++;
      i++;
    }
    while (ris[i]==1 && i<N) {
      destra++;
      i++;
    }

    // Se non equilibrata, return
    if (sinistra!=destra)
      return;
    else
      sinistra=destra=0;
  }

  // Se OK tutti i controlli precedenti, allora questa soluzione potrebbe essere quella finale
  for (i = 0; i < N; i++)
    fin[i]=sol[i];

  max_scambi=num_scambi;

  return;
}

void stampaSol(int *sol, int N) {
  int i;

  printf("Frecce girate: \n");
  for (i = 0; i < N; i++)
    if (sol[i]==1)
      printf("- Posizione %d\n", i);

  return;
}
