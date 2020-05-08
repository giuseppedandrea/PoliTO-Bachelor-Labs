#include <stdio.h>
#include <stdlib.h>

float valutaHorner(float P[], float x, int n);

int main(int argc, char const *argv[]) {
  int i, n, a, b, M;
  float P[11], h, x, risultato=0;

  printf("Grado n: ");
  scanf("%d", &n);

  for (i = n; i >= 0; i--) {
    printf("Coefficiente x^%d: ", i);
    scanf("%f", &P[i]);
  }

  printf("Estremo di integrazione a: ");
  scanf("%d", &a);

  printf("Estremo di integrazione b: ");
  scanf("%d", &b);

  printf("Sottointervalli M: ");
  scanf("%d", &M);

  h=(float)(b-a)/(float)M; //Ampiezza singoli sottointervalli

  x=(float)a+(h/2.0); //Punto medio del primo sottointervallo

  for (i = 0; i < M; i++) {
    risultato+=valutaHorner(P, x, n);
    x+=h; //Aggiornamento punto medio
  }

  printf("L'integrale vale: %.2f\n", h*risultato);

  return 0;
}

float valutaHorner(float P[], float x, int n) {
  int i;
  float px=0;
  //Metodo di Horner
  for (i = n; i >= 0; i--)
    px=(px*x)+P[i];

  return(px);
}
