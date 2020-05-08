#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXF 11
#define MAXP 21

void controllaFile(FILE *fp);
int numVocali(char parola[], int lunghezza);

int main(int argc, char const *argv[]) {
  FILE *fp_in, *fp_out1, *fp_out2;
  char nomeFileIn[MAXF], nomeFileOut1[MAXF], nomeFileOut2[MAXF], parolaP[MAXP], parolaRiga[MAXP];
  int i, n, n_vocali_P;

  printf("Inserisci nome del file da leggere: ");
  scanf("%s", nomeFileIn);
  printf("Inserisci nome del file da scrivere (1): ");
  scanf("%s", nomeFileOut1);
  printf("Inserisci nome del file da scrivere (2): ");
  scanf("%s", nomeFileOut2);

  fp_in=fopen(nomeFileIn, "r");
  controllaFile(fp_in);
  fp_out1=fopen(nomeFileOut1, "w");
  controllaFile(fp_out1);
  fp_out2=fopen(nomeFileOut2, "w");
  controllaFile(fp_out2);

  fscanf(fp_in, "%d %s", &n, parolaP);

  n_vocali_P=numVocali(parolaP, strlen(parolaP));

  for (i = 0; i < n; i++) {
    fscanf(fp_in, "%s", parolaRiga);
    if (strcmp(parolaP, parolaRiga)<0) {
      fprintf(fp_out1, "%s\n", parolaRiga);
    }
    if (numVocali(parolaRiga, strlen(parolaRiga))>=n_vocali_P) {
      fprintf(fp_out2, "%s\n", parolaRiga);
    }
  }

  fclose(fp_in);
  fclose(fp_out1);
  fclose(fp_out2);

  return 0;
}

void controllaFile(FILE *fp) {
  if(fp==NULL) {
    printf("Errore nell'apertura del file!\n");
    exit(EXIT_FAILURE);
  }
  return;
}

int numVocali(char parola[], int lunghezza) {
  int i, j;
  int nVocali=0;
  char listaVocali[10]={'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'};
  for (i = 0; i < lunghezza; i++) {
    for (j = 0; j < 10; j++) {
      if (parola[i]==listaVocali[j]) {
        nVocali++;
        break;
      }
    }
  }
  return(nVocali);
}
