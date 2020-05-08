#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXS 6
#define PRECEDENTE "PREV"

float operando(char s[], float precendente);

int main(int argc, char const *argv[]) {
  char stringa1[MAXS], stringa2[MAXS], operatore;
  float risultato=0;
  int continua=1;

  while (continua) {
    //Acquisizione il primo carattere per determinare l'operazione da effettuare
    scanf(" %c", &operatore);
    switch (operatore) {
      case '+':
        scanf("%s %s", stringa1, stringa2);
        risultato=operando(stringa1, risultato)+operando(stringa2, risultato);
        printf("Risultato: %.2f\n", risultato);
        break;
      case '-':
        scanf("%s %s", stringa1, stringa2);
        risultato=operando(stringa1, risultato)-operando(stringa2, risultato);
        printf("Risultato: %.2f\n", risultato);
        break;
      case '*':
        scanf("%s %s", stringa1, stringa2);
        risultato=operando(stringa1, risultato)*operando(stringa2, risultato);
        printf("Risultato: %.2f\n", risultato);
        break;
      case '/':
        scanf("%s %s", stringa1, stringa2);
        risultato=operando(stringa1, risultato)/operando(stringa2, risultato);
        printf("Risultato: %.2f\n", risultato);
        break;
      default:
        //In caso di operatore non valido terminare il programma
        continua=0;
        printf("Fine\n");
        break;
    }
  }

  return 0;
}

// La funzione confronta s[] con "PREV": se uguale restituisce il risultato della precedente operazione passato nel main(); se diverso converte s[] in float
float operando(char s[], float precendente) {
  if (!strcmp(s, PRECEDENTE))
    return(precendente);
  else
    return(atof(s));
}
