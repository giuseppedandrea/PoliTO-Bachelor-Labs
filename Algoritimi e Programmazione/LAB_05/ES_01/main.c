#include <stdio.h>

int sequenzaHofstadter(int N);

int main(int argc, char const *argv[]) {
  int i, N, seq;

  printf("Inserire numero intero positivo: ");
  scanf("%d", &N);

  for (i = 1; i <= N; i++) {
    seq=sequenzaHofstadter(i);
    printf("%d ", seq);
  }
  printf("\n");

  return(0);
}

int sequenzaHofstadter(int N) {
  int ris;

  if (N==1 || N==2) {
    return(1);
  }

  ris=sequenzaHofstadter(N-sequenzaHofstadter(N-1))+sequenzaHofstadter(N-sequenzaHofstadter(N-2));

  return(ris);
}
