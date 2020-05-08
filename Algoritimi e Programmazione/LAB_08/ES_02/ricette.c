#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ricette.h"

//Acquisizione ricette
linkRicette generazioneRicette(void) {
  int i;
  FILE *fp_ricette;
  linkRicetta new_ricetta=(linkRicetta)malloc(sizeof(*new_ricetta));
  linkRicette ricette=(linkRicette)malloc(sizeof(*ricette));

  ricette->head=ricette->tail=NULL;

  if ((fp_ricette=fopen(NOME_FILE_RICETTE, "r"))==NULL) {
    printf("Errore nell'apertura del file!\n");
    exit(EXIT_FAILURE);
  }

  fscanf(fp_ricette, "%d", &ricette->tot_ricette);

  for (i = 0; i < ricette->tot_ricette; i++) {
    fscanf(fp_ricette, "%s %d", new_ricetta->nome, &new_ricetta->tempo);
    new_ricetta->next=NULL;

    listInsTailRicetta(ricette, new_ricetta, fp_ricette);
  }

  free(new_ricetta);
  fclose(fp_ricette);

  return(ricette);
}

//Inserimenti in coda
void listInsTailRicetta(linkRicette ricette, linkRicetta new_ricetta, FILE *fp_ricette) {
  if ((ricette->head)==NULL) {
    ricette->head=ricette->tail=newNodeRicetta(new_ricetta, fp_ricette);
    return;
  }

  ricette->tail->next=newNodeRicetta(new_ricetta, fp_ricette);
  ricette->tail=ricette->tail->next;

  return;
}

//Creazione nodo in coda
linkRicetta newNodeRicetta(linkRicetta new_ricetta, FILE *fp_ricette) {
  linkRicetta x=(linkRicetta)malloc(sizeof(*x));
  if (x==NULL)
    return(NULL);

  strcpy(x->nome, new_ricetta->nome);
  x->tempo=new_ricetta->tempo;
  x->ingredienti_ricetta=generazioneIngredientiRicetta(fp_ricette);
  x->next=new_ricetta->next;

  return(x);
}

//Ricerca ricetta
linkRicetta ricercaRicetta(linkRicette ricette) {
  linkRicetta x=ricette->head;
  int i;
  char nome_ricetta[MAX_CHAR_NOME_RICETTA];

  printf("Inserisci nome ricetta: ");
  scanf("%s)", nome_ricetta);

  for (i = 0; i < ricette->tot_ricette; i++) {
    if (!strcmp(nome_ricetta, x->nome))
      break;

    x=x->next;
  }

  return(x);
}

//Stampa ricette
void stampaRicette(linkRicette ricette) {
  linkRicetta x=ricette->head;
  int i;

  printf("Elenco ricette:\n");
  for (i = 0; i < ricette->tot_ricette; i++) {
    printf("%d) ", i+1);
    printfRicetta(x, 0);
    x=x->next;
  }

  return;
}
//Stampa ricetta
void stampaRicetta(linkRicette ricette) {
  linkRicetta x;

  x=ricercaRicetta(ricette);

  if (x==NULL)
    printf("Ricetta non trovata!\n");
  else
    printfRicetta(x, 1);

  return;
}

//Printf ricetta
void printfRicetta(linkRicetta ricetta, int dettagli) {
  printf("Nome: %s\n", ricetta->nome);
  if (dettagli==1) {
    printf("Tempo: %d min\n", ricetta->tempo);
    stampaIngredientiRicetta(ricetta->ingredienti_ricetta);
  }

  return;
}

//Free ricette e struct wrapper
void freeRicette(linkRicette ricette) {
  linkRicetta x=ricette->head, x_next;
  linkIngredienteRicetta y, y_next;
  int i, j;

  for (i = 0; i < ricette->tot_ricette; i++) {
    y=x->ingredienti_ricetta->head;
    for (j = 0; j < x->ingredienti_ricetta->tot_ingredienti; j++) {
      y_next=y->next;
      free(y);
      y=y_next;
    }

    x_next=x->next;
    free(x);
    x=x_next;
  }

  free(ricette);

  return;
}

//Calcolo costo
void calcoloCosto(linkRicette ricette, linkIngredienti ingredienti) {
  linkRicetta x;
  float costo;

  x=ricercaRicetta(ricette);

  if (x==NULL)
    printf("Ricetta non trovata!\n");
  else {
    costo=calcoloCostoR(x->ingredienti_ricetta->head, ingredienti);
    printf("Costo ricetta: %.2f\n", costo);
  }

  return;
}

//Calcolo costo ricorsiva
float calcoloCostoR(linkIngredienteRicetta ingrediente_ricetta, linkIngredienti ingredienti) {
  float costo;
  int i;

  if (ingrediente_ricetta==NULL)
    return(0);

  i=ricercaIngrediente(ingredienti, ingrediente_ricetta->nome);

  if (i==-1)
    costo=0;
  else
    costo=(float)(ingrediente_ricetta->grammi)*(ingredienti->ingrediente[i].costo/(float)1000);

  return(costo+(calcoloCostoR(ingrediente_ricetta->next, ingredienti)));
}

//Calcolo calorie
void calcoloCalorie(linkRicette ricette, linkIngredienti ingredienti) {
  linkRicetta x;
  float calorie;

  x=ricercaRicetta(ricette);

  if (x==NULL)
    printf("Ricetta non trovata!\n");
  else  {
    calorie=calcoloCalorieR(x->ingredienti_ricetta->head, ingredienti);
    printf("Calorie ricetta: %.2f\n", calorie);
  }

  return;
}

//Calcolo calorie ricorsiva
float calcoloCalorieR(linkIngredienteRicetta ingrediente_ricetta, linkIngredienti ingredienti) {
  float calorie;
  int i;

  if (ingrediente_ricetta==NULL)
    return(0);

  i=ricercaIngrediente(ingredienti, ingrediente_ricetta->nome);

  if (i==-1)
    calorie=0;
  else
    calorie=(float)(ingrediente_ricetta->grammi)*(ingredienti->ingrediente[i].calorie);

  return(calorie+(calcoloCalorieR(ingrediente_ricetta->next, ingredienti)));
}

//Ricerca ingrediente in ricetta
void ricercaIngredienteRicette(linkRicette ricette, linkIngredienti ingredienti) {
  int i, j;
  char nome_ingrediente[MAX_CHAR_NOME_INGREDIENTE];
  linkRicetta x=ricette->head;
  linkIngredienteRicetta ingrediente_ricetta;

  printf("Inserisci nome ingrediente: ");
  scanf("%s", nome_ingrediente);

  j=ricercaIngrediente(ingredienti, nome_ingrediente);
  if (j==-1) {
    printf("Ingrediente non trovato!\n");
    return;
  }

  printf("Elenco ricette con %s:\n", nome_ingrediente);
  for (i = 0, j = 1; i < ricette->tot_ricette; i++) {
    ingrediente_ricetta=ricercaIngredienteRicetta(x->ingredienti_ricetta, nome_ingrediente);

    if (ingrediente_ricetta!=NULL) {
      printf("%d) ", j++);
      printfRicetta(x, 0);
    }

    x=x->next;
  }

  return;
}

//Inserire ricetta
void inserisciRicetta(linkRicette ricette) {
  linkRicetta new_ricetta=(linkRicetta)malloc(sizeof(*new_ricetta));

  (ricette->tot_ricette)++;

  printf("Inserisci nome ricetta: ");
  scanf("%s", new_ricetta->nome);

  printf("Inserisci tempo ricetta: ");
  scanf("%d", &new_ricetta->tempo);

  new_ricetta->next=NULL;

  listInsTailRicetta(ricette, new_ricetta, stdin);

  free(new_ricetta);

  return;
}
