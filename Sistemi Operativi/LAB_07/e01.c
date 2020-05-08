#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void binary(int *, int, int);

int main (int argc, char *argv[]) {
  int i, j, n;
  int *vet;

  if (argc != 2) {
    printf("Usage: %s <n>\n", argv[0]);
    exit(1);
  }

  n = atoi (argv[1]);

  vet = (int *)malloc(n * sizeof(int));
  if (vet == NULL) {
    printf("Allocatin Error.\n");
    exit(1);
  }

  printf("(Recursive) Binary Numbers:\n");
  binary(vet, n, 0);

  printf("(Concorrent) Binary Numbers:\n");
  for (i=0; i<(2<<(n-1)); i++) {
    if (fork() == 0) {
      for (j=0; j<n; j++) {
        vet[j]=i%2;
        i>>=1;
      }

      for (j=n-1; j>=0; j--) {
        printf("%d", vet[j]);
      }
      printf("\n");

      break;
    }
  }

  free(vet);

  return 0;
}

void binary (int *vet, int n, int i) {
  int j;

  if (i >= n) {
    for (j=0; j<n; j++) {
      printf("%d", vet[j]);
    }
    printf("\n");
    return;
  }

  vet[i] = 0;
  binary(vet, n, i+1);

  vet[i] = 1;
  binary(vet, n, i+1);

  return;
}



