#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME_SORGENTE "sorgente.txt"
#define FILE_NAME_DIZIONARIO "dizionario.txt"
#define FILE_NAME_COMPRESSO "compresso.txt"
#define MAX_DIZIONARIO 30
#define MAX_STRINGA 10
#define MAX_RIGA 200

void controllaFile(FILE *fp);

int main(int argc, char const *argv[]) {
  FILE *fp_sorgente, *fp_dizionario, *fp_compresso;
  int i, j, k, n_dizionario, len_riga, len_dizionario, stringa_uguale, stringa_trovata;
  char dizionario[MAX_DIZIONARIO][MAX_STRINGA], stringaRiga[MAX_RIGA];

  fp_dizionario=fopen(FILE_NAME_DIZIONARIO, "r");

  //Lettura numero di parole nel dizionario
  fscanf(fp_dizionario, "%d", &n_dizionario);
  controllaFile(fp_dizionario);

  //Lettura delle parole del dizionario
  for (i = 0; i < n_dizionario; i++)
    fscanf(fp_dizionario, "%*s %s", dizionario[i]);

  fclose(fp_dizionario);

  fp_sorgente=fopen(FILE_NAME_SORGENTE, "r");
  controllaFile(fp_sorgente);
  fp_compresso=fopen(FILE_NAME_COMPRESSO, "w");
  controllaFile(fp_compresso);

  //Lettura riga per riga del file sorgente
  while(fgets(stringaRiga, MAX_RIGA, fp_sorgente)!=NULL) {
    len_riga=strlen(stringaRiga);
    //Numero di iterazioni: intera lunghezza della riga (non tolgo il '\n' per poterlo stampare successivamente)
    for (i = 0; i < len_riga; i++) {
      stringa_trovata=0;
      //Scorrimento dizionario
      for (j = 0; j < n_dizionario && !stringa_trovata; j++) {
        len_dizionario=strlen(dizionario[j]);
        //(i+len_dizionario-1) -> ultimo carattere della riga
        //(len_riga-1) -> '\n'
        if ((i+len_dizionario-1)<(len_riga-1)) {
          stringa_uguale=1;
          //Controllo degli n caratteri successivi per verficare corrispondenza parola-dizionario
          for (k = 0; k < len_dizionario && stringa_uguale; k++)
            if (dizionario[j][k]!=stringaRiga[i+k])
              stringa_uguale=0;
          if (stringa_uguale)
            stringa_trovata=1;
        }
      }
      //Se c`e' corrispondenza parola-dizionario stampa la versione compressa e incrementata l'indice i della lunghezza della parola, altrimenti stampa il carattere corrente 
      if (stringa_trovata) {
        fprintf(fp_compresso, "$%d", j); //j gia' incrementata dal ciclo precedente
        i+=(len_dizionario-1); //i viene ulteriormente incrementata alla fine di questo ciclo
      } else {
        fprintf(fp_compresso, "%c", stringaRiga[i]);
      }
    }
  }

  fclose(fp_sorgente);
  fclose(fp_compresso);

  return 0;
}

void controllaFile(FILE *fp)
{
  if(fp==NULL)
  {
    printf("Errore nell'apertura del file!\n");
    exit(EXIT_FAILURE);
  }
  return;
}
