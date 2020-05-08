#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_ACCESSI "accessi.txt"
#define MAXN 1000
#define MAXS 31
#define MAXC 8

//Enumerazione per il comando
typedef enum {r_nome, r_IP, r_rifiuto, r_risorse, r_fine, r_err} comando_e;

//Struttura per il salvataggio dei log
typedef struct {
  char IP[MAXS], user[MAXS], risorsa[MAXS];
  int data;
  int risposta;
} Tabella;

void controllaFile(FILE *fp);
int leggiTabella(Tabella log[], FILE *fp);
comando_e leggi_comando(void);
void selezionaDati(Tabella log[], int nDati, comando_e codiceComando);

int main(int argc, char const *argv[]) {
  FILE *fp_in;
  int nDati, continua;
  Tabella log[MAXN];
  comando_e codiceComando;

  fp_in=fopen(FILE_ACCESSI, "r");
  controllaFile(fp_in);

  //Leggi il file degli accessi e ritorna il numero di dati letti
  nDati=leggiTabella(log, fp_in);

  fclose(fp_in);

  continua=1;
  while (continua) {
    //Leggi il comando inserito da tastiera e ritorna il relativo codice (di tipo comando_e)
    codiceComando = leggi_comando();

    //Se il comando e' diverso da "fine"...
    if (codiceComando!=r_fine)
      //Seleziona e stampa a schermo i dati richiesti dal comando
      selezionaDati(log, nDati, codiceComando);
    //... altrimenti termina l'esecuzione del programma
    else
      continua=0;
  }

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

int leggiTabella(Tabella log[], FILE *fp) {
  int i, nDati, giorno, mese, anno;

  //Leggi il numero di righe di log
  fscanf(fp, "%d", &nDati);

  //Per ogni riga di log salva l'ip, l'user, la data, la risorsa e la risposta
  for (i = 0; i < nDati && i < MAXN; i++) {
    fscanf(fp, "%s %s %d/%d/%d:%*s %*s %s %d", log[i].IP, log[i].user, &giorno, &mese, &anno, log[i].risorsa, &log[i].risposta);
    log[i].data=(anno*10000)+(mese*100)+giorno;
  }

  return(nDati);
}

comando_e leggi_comando(void) {
  char cmd[MAXC];
  char elencoComandi[r_err][MAXC] = {"nome", "IP", "rifiuto", "risorsa", "fine"};
  int n_comando;

  //Inserimento comando
  printf("Inserire comando: ");
  scanf("%s", cmd);

  //Scorre il vettore elencoComandi incrementando di volta in volta l'indice dell'enum finche' non c`e' corrispondenza tra comando inserito da tastiera (cmd) e comando del vettore elencoComandi
  n_comando=r_nome;
  while (n_comando<r_err && strcmp(cmd, elencoComandi[n_comando])!=0)
    n_comando++;

  //Ritorna il codice del comando (di tipo comando_e)
  return((comando_e)n_comando);
}

void selezionaDati(Tabella log[], int nDati, comando_e codiceComando) {
  int i, giorno, mese, anno, inf_data, sup_data;

  //Se il comando non e' corretto stampa a schermo un messaggio di errore e ritorna al chiamante
  if(codiceComando==r_err) {
    printf("Comando errato!\n");
    return;
  }

  //Se il comando e' diverso da "rifiuto" (non necessita di un intervallo di date), richiede l'inserimento del range di date
  if (codiceComando!=r_rifiuto) {
    printf("Limite inferiore data (gg/mm/aaaa): ");
    scanf("%d/%d/%d", &giorno, &mese, &anno);

    inf_data=(anno*10000)+(mese*100)+giorno;

    printf("Limite superiore data (gg/mm/aaaa): ");
    scanf("%d/%d/%d", &giorno, &mese, &anno);

    sup_data=(anno*10000)+(mese*100)+giorno;
  }

  //In base al comando inserito, filtra per data (se richiesto) e stampa a schermo il dato richiesto
  switch (codiceComando) {
    case r_nome:
      for (i = 0; i < nDati; i++) {
        if (log[i].data>=inf_data && log[i].data<=sup_data)
          printf("%s\n", log[i].user);
      }
      break;
    case r_IP:
      for (i = 0; i < nDati; i++) {
        if (log[i].data>=inf_data && log[i].data<=sup_data)
          printf("%s\n", log[i].IP);
      }
      break;
    case r_rifiuto:
      for (i = 0; i < nDati; i++) {
        if (log[i].risposta==401)
          printf("%s\n", log[i].user);
      }
      break;
    case r_risorse:
      for (i = 0; i < nDati; i++) {
        if (log[i].data>=inf_data && log[i].data<=sup_data)
          printf("%s\n", log[i].risorsa);
      }
      break;
    default:
      break;
  }

  return;
}
