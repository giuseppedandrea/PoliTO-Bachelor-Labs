#include <stdio.h>

void conversioneBase(int n, int b);

int main(int argc, char const *argv[]) {
  int n, b;

  printf("Inserire numero: ");
  scanf("%d", &n);

  printf("Inserire base (>=2): ");
  scanf("%d", &b);

  conversioneBase(n, b);
  printf("\n");

  return(0);
}

void conversioneBase(int n, int b) {
  int quoziente, resto;

  quoziente=n/b;
  if (quoziente)
    conversioneBase(quoziente, b);

  resto=n%b;
  if (resto<10)
    printf("%d ", resto);
  else
    printf("%c ", ('A'+resto-10));

  return;
}
