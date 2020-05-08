#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

#define MAX_CHAR_NOME_CATEGORIA 255+1
#define MAX_CHAR_NOME_ELEMENTO 255+1
#define NOME_FILE_ELEMENTI "elementi.txt"

float difficolta_massima;
float punteggio_ottimo=0, difficolta_ottima=FLT_MAX;
int **soluzione_ottima;
float punteggio_greedy=0, difficolta_greedy=0;
int **soluzione_greedy;
unsigned long long sottogruppi_totali=0, sottogruppi_pruning=0, combinazioni_totali=0, moltiplicazioni_totali=0, moltiplicazioni_greedy=0; //DEBUG

typedef struct elemento structElemento, *linkElemento;

struct elemento {
  char nome[MAX_CHAR_NOME_ELEMENTO];
  float punti, difficolta;
};

typedef struct categoria structCategoria, *linkCategoria;

struct categoria {
  char nome[MAX_CHAR_NOME_CATEGORIA];
  int num_elementi, min_elementi, max_elementi;
  float min_punti, max_punti, min_difficolta, max_difficolta;
  linkElemento elemento;
};

typedef struct categorie structCategorie, *linkCategorie;

struct categorie {
  int tot_categorie;
  float min_punti, max_punti, min_difficolta, max_difficolta;
  linkCategoria categoria;
};

linkCategorie generazioneCategorie(void);
linkElemento generazioneElemento(FILE *fp_elementi, int num_elementi);
void generazioneProgrammaOttimo(linkCategorie categorie);
void principioMoltiplicazioneNumElementi(linkCategorie categorie, int pos, int **val, int *sol, int n);
int combinazioniRipetute(linkElemento elemento, int pos, int *val, int **sol, int n, int k, int start, int count, float somma_difficolta, int num_combinazioni, float min_difficolta);
void principioMoltiplicazioneCategorie(linkCategorie categorie, int *num_combinazioni, int *num_elementi, int pos, int ***val, int **sol, int n, float somma_difficolta, float somma_punti);
int numeroCombinazioniRipetute(int pos, int n, int k, int start, int count);
void generazioneProgrammaGreedy(linkCategorie categorie);
void shellSort(linkElemento elemento, int l, int r, int tipo);
void freeCategorie(linkCategorie categorie);

int main(int argc, char const *argv[]) {
  linkCategorie categorie;

  categorie=generazioneCategorie();

  printf("Inserire difficolta' massima: ");
  scanf("%f", &difficolta_massima);

  generazioneProgrammaOttimo(categorie);

  generazioneProgrammaGreedy(categorie);

  freeCategorie(categorie);

  return(0);
}

linkCategorie generazioneCategorie(void) {
  linkCategorie categorie=(linkCategorie)malloc(sizeof(*categorie));
  FILE *fp_elementi;
  int i;

  if ((fp_elementi=fopen(NOME_FILE_ELEMENTI, "r"))==NULL) {
    printf("Errore nell'apertura del file!\n");
    exit(EXIT_FAILURE);
  }

  fscanf(fp_elementi, "%d", &categorie->tot_categorie);

  categorie->categoria=(linkCategoria)malloc((categorie->tot_categorie)*sizeof(*(categorie->categoria)));

  categorie->min_punti=categorie->max_punti=categorie->min_difficolta=categorie->max_difficolta=0;
  for (i = 0; i < (categorie->tot_categorie); i++) {
    fscanf(fp_elementi, "%s", categorie->categoria[i].nome);
    fscanf(fp_elementi, "%d", &(categorie->categoria[i].num_elementi));
    fscanf(fp_elementi, "%d", &(categorie->categoria[i].min_elementi));
    fscanf(fp_elementi, "%d", &(categorie->categoria[i].max_elementi));
    categorie->categoria[i].elemento=generazioneElemento(fp_elementi, categorie->categoria[i].num_elementi);

    shellSort(categorie->categoria[i].elemento, 0, categorie->categoria[i].num_elementi-1, 0);
    categorie->categoria[i].min_punti=categorie->categoria[i].elemento[0].punti*categorie->categoria[i].min_elementi;
    categorie->categoria[i].max_punti=categorie->categoria[i].elemento[categorie->categoria[i].num_elementi-1].punti*categorie->categoria[i].min_elementi;

    shellSort(categorie->categoria[i].elemento, 0, categorie->categoria[i].num_elementi-1, 1);
    categorie->categoria[i].min_difficolta=categorie->categoria[i].elemento[0].difficolta*categorie->categoria[i].min_elementi;
    categorie->categoria[i].max_difficolta=categorie->categoria[i].elemento[categorie->categoria[i].num_elementi-1].difficolta*categorie->categoria[i].min_elementi;

    // printf("- Categoria %d\n", i); // DEBUG
    // printf("Min punti: %.2f\n", categorie->categoria[i].min_punti); // DEBUG
    // printf("Max punti: %.2f\n", categorie->categoria[i].max_punti); // DEBUG
    // printf("Min difficolta: %.2f\n", categorie->categoria[i].min_difficolta); // DEBUG
    // printf("Max difficolta: %.2f\n", categorie->categoria[i].max_difficolta); // DEBUG

    categorie->min_punti+=categorie->categoria[i].min_punti;
    categorie->max_punti+=categorie->categoria[i].max_punti;
    categorie->min_difficolta+=categorie->categoria[i].min_difficolta;
    categorie->max_difficolta+=categorie->categoria[i].max_difficolta;
  }

  // printf("\nMin punti totale: %.2f\n", categorie->min_punti); // DEBUG
  // printf("Max punti totale: %.2f\n", categorie->max_punti); // DEBUG
  // printf("Min difficolta totale: %.2f\n", categorie->min_difficolta); // DEBUG
  // printf("Max difficolta totale: %.2f\n\n", categorie->max_difficolta); // DEBUG

  fclose(fp_elementi);

  return(categorie);
}

linkElemento generazioneElemento(FILE *fp_elementi, int num_elementi) {
  linkElemento elemento=(linkElemento)malloc(num_elementi*sizeof(*elemento));
  int i;

  for (i = 0; i < num_elementi; i++) {
    fscanf(fp_elementi, "%s", elemento[i].nome);
    fscanf(fp_elementi, "%f", &elemento[i].punti);
    fscanf(fp_elementi, "%f", &elemento[i].difficolta);
  }

  return(elemento);
}

void generazioneProgrammaOttimo(linkCategorie categorie) {
  int i, j, size_val_num_elementi;
  int **val_num_elementi, *sol_num_elementi;

  val_num_elementi=(int **)malloc((categorie->tot_categorie)*sizeof(*val_num_elementi));
  for (i = 0; i < (categorie->tot_categorie); i++) {
    size_val_num_elementi=((categorie->categoria[i].max_elementi)-(categorie->categoria[i].min_elementi))+1;
    val_num_elementi[i]=(int *)malloc(size_val_num_elementi*sizeof(*val_num_elementi[i]));
    for (j = 0; j < size_val_num_elementi; j++)
      val_num_elementi[i][j]=(categorie->categoria[i].min_elementi)+j;
    val_num_elementi[i][j]=-1;
  }

  soluzione_ottima=(int **)malloc((categorie->tot_categorie)*sizeof(*soluzione_ottima));

  for (i = 0; i < (categorie->tot_categorie); i++) {
    soluzione_ottima[i]=(int *)malloc((categorie->categoria[i].max_elementi+1)*sizeof(*soluzione_ottima[i]));
    for (j = 0; j < (categorie->categoria[i].max_elementi+1); j++)
      soluzione_ottima[i][j]=-1;
  }

  // printf("## Sottogruppi possibili\n"); //DEBUG

  // for (i = 0; i < (categorie->tot_categorie); i++) { // DEBUG
  //   size_val_num_elementi=((categorie->categoria[i].max_elementi)-(categorie->categoria[i].min_elementi))+1; // DEBUG
  //   printf("Cat. %d: ", i); //DEBUG
  //   for (j = 0; j <= size_val_num_elementi; j++) //DEBUG
  //     printf("%d ", val_num_elementi[i][j]); //DEBUG
  //   printf("\n"); //DEBUG
  // } // DEBUG

  sol_num_elementi=(int *)malloc((categorie->tot_categorie)*sizeof(*sol_num_elementi));

  principioMoltiplicazioneNumElementi(categorie, 0, val_num_elementi, sol_num_elementi, categorie->tot_categorie);

  // printf("\n\n\n"); //DEBUG
  printf("Sottogruppi totali: %llu\n", sottogruppi_totali); //DEBUG
  printf("Sottogruppi pruning: %llu\n", sottogruppi_pruning); //DEBUG
  printf("Combinazioni totali: %llu\n", combinazioni_totali); //DEBUG
  printf("Moltiplicazioni totali: %llu\n\n", moltiplicazioni_totali); //DEBUG

  printf("Difficolta' ottima: %.2f\n", difficolta_ottima);
  printf("Punteggio ottimo: %.3f\n", punteggio_ottimo);
  printf("Programma ottimo:\n");
  for (i = 0; i < categorie->tot_categorie; i++){
    printf("- Categoria %d\n", i+1);
    for (j = 0; soluzione_ottima[i][j] != -1; j++)
      printf("-- %s\n", categorie->categoria[i].elemento[soluzione_ottima[i][j]].nome);
  }
  printf("\n\n");

  return;
}

void principioMoltiplicazioneNumElementi(linkCategorie categorie, int pos, int **val, int *sol, int n) {
  int i;

  if (pos >= n) {
    int j, k, size_valori;
    int ***valori, *cat, *num_combinazioni;

    sottogruppi_totali++; //DEBUG
    // printf("@ Selezione sottogruppi\n"); //DEBUG
    // for (i = 0; i < n; i++) //DEBUG
    //   printf("%d ", sol[i]); //DEBUG
    // printf("\n"); //DEBUG

    valori=(int ***)malloc((categorie->tot_categorie)*sizeof(*valori));

    num_combinazioni=(int *)malloc((categorie->tot_categorie)*sizeof(*num_combinazioni));

    for (i = 0; i < (categorie->tot_categorie); i++) {
      size_valori=numeroCombinazioniRipetute(0, categorie->categoria[i].num_elementi, sol[i], 0, 0);

      valori[i]=(int **)malloc(size_valori*sizeof(*valori[i]));

      for (j = 0; j < size_valori; j++) {
        valori[i][j]=(int *)malloc(sol[i]*sizeof(*valori[i]));
      }

      for (j = 0; j < size_valori; j++)
        for (k = 0; k < sol[i]; k++)
          valori[i][j][k]=0;

      cat=(int *)malloc((categorie->categoria[i].num_elementi)*sizeof(*cat));

      for (j = 0; j < categorie->categoria[i].num_elementi; j++)
        cat[j]=j;

      // printf("@@ Possibili combinazioni cat. %d - k=%d\n", i, sol[i]); //DEBUG

      num_combinazioni[i]=combinazioniRipetute(categorie->categoria[i].elemento, 0, cat, valori[i], categorie->categoria[i].num_elementi, sol[i], 0, 0, 0, size_valori, categorie->min_difficolta-categorie->categoria[i].min_difficolta);

      free(cat);

      // Pruning sottogruppi nulli
      if (num_combinazioni[i] == 0)
        return;
    }

    // printf("@@ Numero combinazioni\n"); //DEBUG
    // for (i = 0; i < (categorie->tot_categorie); i++) { //DEBUG
    //   printf("cat. %d: %d\n", i, num_combinazioni[i]); //DEBUG
    // } //DEBUG

    sottogruppi_pruning++; //DEBUG

    int **soluzione=(int **)malloc((categorie->tot_categorie)*sizeof(*soluzione));

    for (i = 0; i < (categorie->tot_categorie); i++) {
      soluzione[i]=(int *)malloc(sol[i]*sizeof(*soluzione[i]));
      for (j = 0; j < sol[i]; j++)
        soluzione[i][j]=0;
    }

    // printf("@@@ Combinazione categorie\n"); //DEBUG

    principioMoltiplicazioneCategorie(categorie, num_combinazioni, sol, 0, valori, soluzione, categorie->tot_categorie, 0, 0);

    return;
  }

  for (i = 0; val[pos][i]!=-1; i++) {
    sol[pos]=val[pos][i];
    principioMoltiplicazioneNumElementi(categorie, pos+1, val, sol, n);
  }

  return;
}

int combinazioniRipetute(linkElemento elemento, int pos, int *val, int **sol, int n, int k, int start, int count, float somma_difficolta, int num_combinazioni, float min_difficolta) {
  int i;

  if (pos >= k) {
    // printf("comb %d\n", num_combinazioni); //DEBUG
    // printf("count %d\n", count); //DEBUG

    // for (i = 0; i < k; i++) //DEBUG
    //   printf("%d ", sol[count][i]); //DEBUG
    // printf("%.2f\n", somma_difficolta); //DEBUG

    if ((min_difficolta+somma_difficolta) > difficolta_massima)
      return(count);

    combinazioni_totali++; //DEBUG

    if (count+1 < num_combinazioni)
      for (i = 0; i < k; i++)
        sol[count+1][i]=sol[count][i];

    return(count+1);
  }

  for (i = start; i < n; i++) {
    sol[count][pos]=val[i];

    // Pruning somma difficolta'
    if ((somma_difficolta+elemento[sol[count][pos]].difficolta) <= difficolta_massima)
      count=combinazioniRipetute(elemento, pos+1, val, sol, n, k, start++, count, somma_difficolta+elemento[sol[count][pos]].difficolta, num_combinazioni, min_difficolta);
  }

  return(count);
}

void principioMoltiplicazioneCategorie(linkCategorie categorie, int *num_combinazioni, int *num_elementi, int pos, int ***val, int **sol, int n, float somma_difficolta, float somma_punti) {
  int i, j, k, tmp;
  float somma_parziale_difficolta, somma_parziale_punti;

  if (pos >= n) {
    moltiplicazioni_totali++; //DEBUG

    // for (i = 0; i < n; i++) //DEBUG
    //   for (j = 0; j < num_elementi[i]; j++) //DEBUG
    //     printf("%d ", sol[i][j]); //DEBUG
    // printf("\n"); //DEBUG
    //
    // for (i = 0; i < n; i++) //DEBUG
    //   for (j = 0; j < num_elementi[i]; j++) //DEBUG
    //     printf("%s\n", categorie->categoria[i].elemento[sol[i][j]].nome); //DEBUG
    //
    // printf("=====\n"); //DEBUG
    // printf("Difficolta: %.2f\n", somma_difficolta); //DEBUG
    // printf("Punteggio: %.3f\n\n", somma_punti); //DEBUG

    if (somma_punti >= punteggio_ottimo) {
      if (somma_punti == punteggio_ottimo) {
        if (somma_difficolta < difficolta_ottima) {
          punteggio_ottimo=somma_punti;
          difficolta_ottima=somma_difficolta;
        }
      }

      if (somma_punti > punteggio_ottimo) {
        punteggio_ottimo=somma_punti;
        difficolta_ottima=somma_difficolta;
      }

      for (i = 0; i < n; i++) {
        for (j = 0; j < num_elementi[i]; j++)
          soluzione_ottima[i][j]=sol[i][j];
        soluzione_ottima[i][j]=-1;
      }
    }

    return;
  }

  for (i = 0; i < num_combinazioni[pos]; i++) {
    sol[pos]=val[pos][i];

    // Calcolo difficolta'
    for (j = 0, somma_parziale_difficolta=0; j < num_elementi[pos]; j++)
      somma_parziale_difficolta+=categorie->categoria[pos].elemento[sol[pos][j]].difficolta;

    if ((somma_difficolta+somma_parziale_difficolta) <= difficolta_massima) { // Pruning difficolta'
      // Calcolo punteggio
      for (j = 0, somma_parziale_punti=0; j < num_elementi[pos]; j+=k) {
        tmp=sol[pos][j];

        for (k = 0; ((j+k) < num_elementi[pos]) && (sol[pos][j+k] == tmp); k++);

        if (k == 1) {
          somma_parziale_punti+=categorie->categoria[pos].elemento[tmp].punti;
        } else {
          somma_parziale_punti+=categorie->categoria[pos].elemento[tmp].punti;
          somma_parziale_punti+=((categorie->categoria[pos].elemento[tmp].punti)/(float)2);
        }
      }

      principioMoltiplicazioneCategorie(categorie, num_combinazioni, num_elementi, pos+1, val, sol, n, somma_difficolta+somma_parziale_difficolta, somma_punti+somma_parziale_punti);
    }
  }

  return;
}

int numeroCombinazioniRipetute(int pos, int n, int k, int start, int count) {
  int i;

  if (pos >= k)
    return(count+1);

  for (i = start; i < n; i++)
    count=numeroCombinazioniRipetute(pos+1, n, k, start++, count);

  return(count);
}

void generazioneProgrammaGreedy(linkCategorie categorie) {
  int i, j, k, n, tmp;
  float somma_parziale_difficolta=0, somma_resto_difficolta=0, resto_categorie, resto_categoria;

  // for (i = 0; i < (categorie->tot_categorie); i++) { // DEBUG
  //   for (j = 0; val_num_elementi[i][j] != -1; j++) // DEBUG
  //     printf("%d ", val_num_elementi[i][j]); // DEBUG
  //   printf("\n"); // DEBUG
  // } // DEBUG

  soluzione_greedy=(int **)malloc((categorie->tot_categorie)*sizeof(*soluzione_greedy));

  for (i = 0; i < (categorie->tot_categorie); i++) {
    soluzione_greedy[i]=(int *)malloc((categorie->categoria[i].max_elementi+1)*sizeof(*soluzione_greedy[i]));
    for (j = 0; j < (categorie->categoria[i].max_elementi+1); j++)
      soluzione_greedy[i][j]=-1;
  }

  for (i = 0; i < (categorie->tot_categorie); i++) {
    // for (j = 0; j < categorie->categoria[i].num_elementi; j++) { // DEBUG
    //   printf("%s: ", categorie->categoria[i].elemento[j].nome); // DEBUG
    //   printf("%.2f\n", categorie->categoria[i].elemento[j].punti/categorie->categoria[i].elemento[j].difficolta); // DEBUG
    // } // DEBUG
    // printf("\n"); // DEBUG

    shellSort(categorie->categoria[i].elemento, 0, categorie->categoria[i].num_elementi-1, 2);
    somma_resto_difficolta+=categorie->categoria[i].min_difficolta;

    // for (j = 0; j < categorie->categoria[i].num_elementi; j++) { // DEBUG
    //   printf("nome: %20s ", categorie->categoria[i].elemento[j].nome); // DEBUG
    //   printf("\tratio: %.2f", categorie->categoria[i].elemento[j].punti/categorie->categoria[i].elemento[j].difficolta); // DEBUG
    //   printf("\tpunti: %.2f", categorie->categoria[i].elemento[j].punti); // DEBUG
    //   printf("\tdifficolta: %.2f\n", categorie->categoria[i].elemento[j].difficolta); // DEBUG
    // } // DEBUG
    // printf("\n##############\n\n"); // DEBUG
  }

  for (i = 0; i < (categorie->tot_categorie); i++) {
    somma_resto_difficolta-=categorie->categoria[i].min_difficolta;
    // printf("Resto cat. %d: %.2f\n", i, somma_resto_difficolta); // DEBUG

    for (j = 0, somma_parziale_difficolta = 0, n = 0; j < categorie->categoria[i].max_elementi; j++) {
      // printf("\nK: %d\n", j+categorie->categoria[i].min_elementi); // DEBUG
      for (k = j; k < categorie->categoria[i].num_elementi; k++) {
        // printf("\nElemento: %d\n", k); // DEBUG
        resto_categoria=(categorie->categoria[i].min_elementi-n-1)*(categorie->categoria[i].min_difficolta/categorie->categoria[i].min_elementi);
        if (resto_categoria < 0)
          resto_categoria=0;
        // printf("Resto categoria: %.2f\n", resto_categoria); // DEBUG
        resto_categorie=difficolta_greedy+(categorie->categoria[i].elemento[k].difficolta+somma_parziale_difficolta+resto_categoria)+somma_resto_difficolta;
        // printf("Resto categorie: %.2f\n", resto_categorie); // DEBUG
        if (resto_categorie <= difficolta_massima) {
          somma_parziale_difficolta+=categorie->categoria[i].elemento[k].difficolta;
          soluzione_greedy[i][j]=k;
          n++;
          // printf("Preso\n"); // DEBUG
          // printf("Somma parziale %.2f\n", somma_parziale_difficolta); // DEBUG
          break;
        }
      }
    }
    difficolta_greedy+=somma_parziale_difficolta;

    // printf("\nDifficolta greedy %.2f\n", difficolta_greedy); // DEBUG
    // printf("\n-----------------\n\n"); // DEBUG
  }

  // Calcolo punteggio
  for (i = 0; i < categorie->tot_categorie; i++) {
    for (j = 0; soluzione_greedy[i][j] != -1; j+=k) {
      tmp=soluzione_greedy[i][j];

      for (k = 0; (soluzione_greedy[i][j] != -1) && (soluzione_greedy[i][j+k] == tmp); k++);

      if (k == 1) {
        punteggio_greedy+=categorie->categoria[i].elemento[tmp].punti;
      } else {
        punteggio_greedy+=categorie->categoria[i].elemento[tmp].punti;
        punteggio_greedy+=((categorie->categoria[i].elemento[tmp].punti)/(float)2);
      }
    }
  }

  printf("Difficolta' greedy: %.2f\n", difficolta_greedy);
  printf("Punteggio greedy: %.3f\n", punteggio_greedy);
  printf("Programma greedy:\n");
  for (i = 0; i < categorie->tot_categorie; i++){
    printf("- Categoria %d\n", i+1);
    for (j = 0; soluzione_greedy[i][j] != -1; j++)
      printf("-- %s\n", categorie->categoria[i].elemento[soluzione_greedy[i][j]].nome);
  }
  printf("\n\n");

  return;
}

void shellSort(linkElemento elemento, int l, int r, int tipo) {
  int i, j, h=1, n=r-l+1;
  structElemento tmp;

  while (h < n/3)
    h=(3*h)+1;
  while(h >= 1) {
    for (i = l + h; i <= r; i++) {
      j=i;
      tmp = elemento[i];
      // Tipo 0 -> punti (crescente)
      // Tipo 1 -> difficolta (crescente)
      // Tipo 2 -> punti/difficolta (decrescente)
      switch (tipo) {
        case 0:
          while(j >= l + h  && tmp.punti < elemento[j-h].punti) {
            elemento[j]=elemento[j-h];
            j-=h;
          }
          break;
        case 1:
          while(j >= l + h  && tmp.difficolta < elemento[j-h].difficolta) {
            elemento[j]=elemento[j-h];
            j-=h;
          }
          break;
        case 2:
          while(j >= l + h  && tmp.punti/tmp.difficolta > elemento[j-h].punti/elemento[j-h].difficolta) {
            elemento[j]=elemento[j-h];
            j-=h;
          }
          break;
        default:
          printf("Errore nei parametri\n");
          exit(EXIT_FAILURE);
          break;
      }
      elemento[j]=tmp;
    }
    h=h/3;
  }
}

void freeCategorie(linkCategorie categorie) {
  int i;

  for (i = 0; i < categorie->tot_categorie; i++)
    free(categorie->categoria[i].elemento);

  free(categorie->categoria);
  free(categorie);

  free(soluzione_ottima);
  free(soluzione_greedy);

  return;
}
