#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOME_FILE "catalogo.txt"
#define MAXC_CODICE 9
#define MAXC_DATA 11
#define MAXC_NOME 25
#define MAXC_CATEGORIA 25
#define MAXC_COMANDI 18

typedef struct {
  char *nome, *categoria;
  float prezzo;
  int disponibilita, codice;
  char codice_formattato[MAXC_CODICE+1], data[MAXC_DATA+1];
} prodotto;

typedef enum {c_stampa_catalogo, c_ordina_prezzo_asc, c_ordina_prezzo_disc, c_ordina_codice, c_ordina_nome, c_stampa_categoria, c_aggiorna_prodotto, c_ricerca_codice, c_ricerca_nome, c_help, c_fine, c_err} comando_enum;

int letturaCatalogo(FILE *fp, prodotto *catalogo, int N);
void elaboraComando(prodotto *catalogo, int N);
comando_enum leggiComando(char lista_comandi[][MAXC_COMANDI+1]);
void stampaHelp(char lista_comandi[][MAXC_COMANDI+1]);
void stampaCatalogo(prodotto *catalogo, int l, int r);
void stampaCategoria(prodotto *catalogo, int N);
void ordinaProdotto(prodotto *catalogo, int N, int asc_o_disc, int tipo);
int confrontaProdotto(prodotto *catalogo, prodotto tmp, int n, int confronto);
void selezionaChiave(int tipo, char tmp[]);
void aggiornaProdotto(prodotto *catalogo, int N, int ordinamento_codice, char *k);
int ricercaCodice(prodotto *catalogo, int N, int ordinamento_codice, char *k);
void ricercaNome(prodotto *catalogo, int N, char *k);
int ricercaLineare(prodotto *catalogo, int l, int r, char *k, int tipo);
int ricercaDicotomica(prodotto *catalogo, int l, int r, char *k);

int main(int argc, char const *argv[]) {
  FILE *fp_in;
  int N;
  prodotto *catalogo;

  //Apertura file
  if ((fp_in=fopen(NOME_FILE, "r"))==NULL) {
    printf("Errore nell'apertura del file!\n");
    return(EXIT_FAILURE);
  }

  //Lettura catalogo prodotti
  fscanf(fp_in, "%d", &N);

  catalogo=(prodotto *)malloc(N*sizeof(prodotto));

  letturaCatalogo(fp_in, catalogo, N);

  fclose(fp_in);

  //Lettura ed elaborazione comando
  elaboraComando(catalogo, N);

  free(catalogo);

  return 0;
}

int letturaCatalogo(FILE *fp, prodotto *catalogo, int N) {
  int i;
  char nome_prodotto[MAXC_NOME+1], categoria_prodotto[MAXC_CATEGORIA+1];

  //Per ogni riga del catalogo memorizza informazioni prodotto
  for (i = 0; i < N; i++) {
    fscanf(fp, "%s %s %s %f %d %s", catalogo[i].codice_formattato, nome_prodotto, categoria_prodotto, &catalogo[i].prezzo, &catalogo[i].disponibilita, catalogo[i].data);

    //Salvataggio codice come intero
    sscanf(catalogo[i].codice_formattato, "cod%d", &catalogo[i].codice);

    //Vettore di caratteri (nome) allocato dinamicamente
    catalogo[i].nome=(char *)malloc(strlen(nome_prodotto)*sizeof(char));
    strcpy(catalogo[i].nome, nome_prodotto);

    //Vettore di caratteri (categoria) allocato dinamicamente
    catalogo[i].categoria=(char *)malloc(strlen(categoria_prodotto)*sizeof(char));
    strcpy(catalogo[i].categoria, categoria_prodotto);
  }

  return(N);
}

void elaboraComando(prodotto *catalogo, int N) {
  char lista_comandi[c_err][MAXC_COMANDI+1]={"stampa-catalogo", "ordina-prezzo-asc", "ordina-prezzo-disc", "ordina-codice", "ordina-nome", "stampa-categoria", "aggiorna-prodotto", "ricerca-codice", "ricerca-nome", "help", "fine"};
  comando_enum codice_comando;
  int continua=1, ordinamento_codice=0;
  char tmp_k[MAXC_NOME+1];

  while (continua) {
    codice_comando=leggiComando(lista_comandi);

    switch (codice_comando) {
      case c_stampa_catalogo:
        stampaCatalogo(catalogo, 0, N-1);
        break;
      case c_ordina_prezzo_asc:
        ordinaProdotto(catalogo, N-1, 0, 0);
        ordinamento_codice=0;
        break;
      case c_ordina_prezzo_disc:
        ordinaProdotto(catalogo, N-1, 1, 0);
        ordinamento_codice=0;
        break;
      case c_ordina_codice:
        ordinaProdotto(catalogo, N-1, 0, 1);
        ordinamento_codice=1;
        break;
      case c_ordina_nome:
        ordinaProdotto(catalogo, N-1, 0, 2);
        ordinamento_codice=0;
        break;
      case c_stampa_categoria:
        ordinaProdotto(catalogo, N-1, 0, 3);
        ordinamento_codice=0;
        stampaCategoria(catalogo, N);
        break;
      case c_aggiorna_prodotto:
        selezionaChiave(0, tmp_k);
        aggiornaProdotto(catalogo, N, ordinamento_codice, tmp_k);
        break;
      case c_ricerca_codice:
        //selezionaChiave(tipo dato da ricercare)
        //Tipo 0: ricerca chiave per codice
        selezionaChiave(0, tmp_k);
        ricercaCodice(catalogo, N, ordinamento_codice, tmp_k);
        break;
      case c_ricerca_nome:
        //selezionaChiave(tipo dato da ricercare)
        //Tipo 1: ricerca chiave per nome
        selezionaChiave(1, tmp_k);
        ricercaNome(catalogo, N, tmp_k);
        break;
      case c_help:
        stampaHelp(lista_comandi);
        break;
      case c_fine:
        continua=0;
        break;
      case c_err:
      default:
        printf("Comando errato!!!\n\n");
        stampaHelp(lista_comandi);
        break;
    }

    printf("\n");
  }

  return;
}

comando_enum leggiComando(char lista_comandi[][MAXC_COMANDI+1]) {
  char cmd[MAXC_COMANDI+1];
  int n_comando;

  printf("Inserire comando (\"help\" mostra comandi): ");
  scanf("%s", cmd);

  n_comando=c_stampa_catalogo;
  while (n_comando<c_err && strcmp(cmd, lista_comandi[n_comando]))
    n_comando++;

  return((comando_enum)n_comando);
}

void stampaHelp(char lista_comandi[][MAXC_COMANDI+1]) {
  int i;

  printf("Elenco dei comandi:\n");

  for (i = 0; i < c_err; i++)
    printf("%s\n", lista_comandi[i]);

  return;
}

void stampaCatalogo(prodotto *catalogo, int l, int r) {
  int i;

  for (i = l; i <= r; i++) {
    printf("%s %s %s %.2f %d %s\n", catalogo[i].codice_formattato, catalogo[i].nome, catalogo[i].categoria, catalogo[i].prezzo, catalogo[i].disponibilita, catalogo[i].data);
  }

  return;
}

void stampaCategoria(prodotto *catalogo, int N) {
  int l, r=0;

  while (r < N) {
    l=r;
    printf("-Categoria %s:\n", catalogo[l].categoria);
    while (((++r)<N) && !strcmp(catalogo[l].categoria, catalogo[r].categoria));
    stampaCatalogo(catalogo, l, r-1);
  }

  return;
}

//Algoritmo ShellSort con opzione ascendente/discendente
void ordinaProdotto(prodotto *catalogo, int N, int asc_o_disc, int tipo) {
  int i, j, h=1, n = N+1;
  prodotto tmp;

  while (h < n/3)
    h=(3*h)+1;
  while(h >= 1) {
    for (i = h; i <= N; i++) {
      j=i;
      tmp = catalogo[i];
      if(asc_o_disc) {
        while(j >= h && confrontaProdotto(catalogo, tmp, j-h, tipo)) {
          catalogo[j] = catalogo[j-h];
          j-=h;
        }
      } else {
        while(j >= h && !confrontaProdotto(catalogo, tmp, j-h, tipo)) {
          catalogo[j] = catalogo[j-h];
          j-=h;
        }
      }
      catalogo[j]=tmp;
    }
    h=h/3;
  }

  return;
}

int confrontaProdotto(prodotto *catalogo, prodotto tmp, int n, int confronto) {
  //Confronto 0: ordina per prezzo
  //Confronto 1: ordina per codice
  //Confronto 2: ordina per nome
  //Confronto 3: ordina per categoria
  switch (confronto) {
    case 0:
      if (tmp.prezzo>catalogo[n].prezzo)
        return(1);
      else
        return(0);
      break;
    case 1:
      if (tmp.codice>catalogo[n].codice)
        return(1);
      else
        return(0);
      break;
    case 2:
      if (strcmp(tmp.nome, catalogo[n].nome)>0)
        return(1);
      else
        return(0);
      break;
    case 3:
      if (strcmp(tmp.categoria, catalogo[n].categoria)>0)
        return(1);
      else
        return(0);
      break;
    default:
      printf("Errore nell'ordinamento!\n");
      exit(EXIT_FAILURE);
  }
}

void selezionaChiave(int tipo, char tmp[]) {
  //Tipo 0: ricerca chiave per codice
  //Tipo 1: ricerca chiave per nome
  switch (tipo) {
    case 0:
      printf("Inserire codice (codXXXXXX): ");
      scanf("%s", tmp);
      break;
    case 1:
      printf("Inserire nome (anche parziale): ");
      scanf("%s", tmp);
      break;
    default:
      printf("Errore nella ricerca della chiave!\n");
      exit(EXIT_FAILURE);
  }

  return;
}

void aggiornaProdotto(prodotto *catalogo, int N, int ordinamento_codice, char *k) {
  int indice, unita;
  char data[MAXC_DATA+1];

  indice=ricercaCodice(catalogo, N, ordinamento_codice, k);

  if(indice!=-1) {
    printf("\nInserisci unita' disponibili: ");
    scanf("%d", &unita);

    catalogo[indice].disponibilita=unita;

    printf("Inserisci data odierna (gg/mm/aaaa): ");
    scanf("%s", data);

    strcpy(catalogo[indice].data, data);
  }

  return;
}

int ricercaCodice(prodotto *catalogo, int N, int ordinamento_codice, char *k) {
  int indice;

  if (ordinamento_codice) {
    //ricercaDicotomica(struct, l, r, chiave)
    indice=ricercaDicotomica(catalogo, 0, N-1, k);
  } else {
    //ricercaLineare(struct, l, r, chiave, tipo dato da ricercare)
    //Tipo 0: ricerca chiave per codice
    indice=ricercaLineare(catalogo, 0, N-1, k, 0);
  }
  if(indice!=-1)
    stampaCatalogo(catalogo, indice, indice);
  else
    printf("Codice non trovato!\n");

  return(indice);
}

void ricercaNome(prodotto *catalogo, int N, char *k) {
  int indice=0;

  while (indice!=-1) {
    //ricercaLineare(struct, l, r, chiave, tipo dato da ricercare)
    //Tipo 1: ricerca chiave per nome
    indice=ricercaLineare(catalogo, indice, N-1, k, 1);

    if(indice!=-1) {
      stampaCatalogo(catalogo, indice, indice);
      indice++;
    }
  }

  return;
}

int ricercaLineare(prodotto *catalogo, int l, int r, char *k, int tipo) {
  int i=l;
  int found=0;

  while (i <= r && !found)
    //Tipo 0: ricerca chiave per codice
    //Tipo 1: ricerca chiave per nome
    switch (tipo) {
      case 0:
        if (!strcmp(k, catalogo[i].codice_formattato))
          found=1;
        else
          i++;
        break;
      case 1:
        if (strstr(catalogo[i].nome, k)!=NULL)
          found=1;
        else
          i++;
        break;
      default:
        printf("Errore nella ricerca della chiave!\n");
        exit(EXIT_FAILURE);
    }

  if (!found)
    return(-1);
  else
    return(i);
}

int ricercaDicotomica(prodotto *catalogo, int l, int r, char *k) {
  int m;

  while(l <= r){
    m = l+((r-l)/2);
    if(!strcmp(catalogo[m].codice_formattato, k))
      return(m);
    if(strcmp(catalogo[m].codice_formattato, k)<0)
      l = m+1;
    else
      r = m-1;
  }

  return(-1);
}
