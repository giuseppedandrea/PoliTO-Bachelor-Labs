#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ingredienti.h"

//struct wrapper ingredienti
struct ingredienti {
  linkIngrediente ingrediente;
  int tot_ingredienti;
};

//struct ingrediente
struct ingrediente {
  char nome[MAX_CHAR_NOME_INGREDIENTE];
  float costo;
  float calorie;
};

//Acquisizione ingredienti
linkIngredienti generazioneIngredienti() {
  int i;
  FILE *fp_ingredienti;
  char nome_ingrediente[MAX_CHAR_NOME_INGREDIENTE];
  linkIngredienti ingredienti=(linkIngredienti)malloc(sizeof(*ingredienti));

  if ((fp_ingredienti=fopen(NOME_FILE_INGREDIENTI, "r"))==NULL) {
    printf("Errore nell'apertura del file!\n");
    exit(EXIT_FAILURE);
  }

  fscanf(fp_ingredienti, "%d", &ingredienti->tot_ingredienti);

  ingredienti->ingrediente=(linkIngrediente)malloc(ingredienti->tot_ingredienti*sizeof(*ingredienti->ingrediente));

  for (i = 0; i < ingredienti->tot_ingredienti; i++) {
    fscanf(fp_ingredienti, "%s %f %f", nome_ingrediente, &(ingredienti->ingrediente[i].costo), &(ingredienti->ingrediente[i].calorie));
    strcpy(ingredienti->ingrediente[i].nome, nome_ingrediente);
  }

  fclose(fp_ingredienti);

  return(ingredienti);
}

//Ricerca ingredienti
int ricercaIngrediente(linkIngredienti ingredienti, char nome_ingrediente[MAX_CHAR_NOME_INGREDIENTE]) {
  int i;

  for (i = 0; i < ingredienti->tot_ingredienti; i++)
    if (strcmp(nome_ingrediente, ingredienti->ingrediente[i].nome)==0)
      return(i);

  return(-1);
}

//Stampa ingredienti
void stampaIngredienti(linkIngredienti ingredienti) {
  int i;

  printf("Elenco ingredienti:\n");
  for (i = 0; i < ingredienti->tot_ingredienti; i++) {
    printf("%d) ", i+1);
    printfIngrediente(&ingredienti->ingrediente[i], 0);
  }

  return;
}

//Stampa ingrediente
void stampaIngrediente(linkIngredienti ingredienti) {
  char nome_ingrediente[MAX_CHAR_NOME_INGREDIENTE];
  int i;

  printf("Inserisci nome ingrediente: ");
  scanf("%s", nome_ingrediente);

  i=ricercaIngrediente(ingredienti, nome_ingrediente);

  if (i==-1)
    printf("Ingrediente non trovato!\n");
  else
    printfIngrediente(&ingredienti->ingrediente[i], 1);

  return;
}

//Printf ingrediente
void printfIngrediente(linkIngrediente ingrediente, int dettagli) {
  printf("Nome: %s\n", ingrediente->nome);
  if (dettagli==1)
    printf("Costo: %.2f\nCalorie: %.2f\n", ingrediente->costo, ingrediente->calorie);

  return;
}

//Free ingredienti
void freeIngredienti(linkIngredienti ingredienti) {
  free(ingredienti);

  return;
}

//struct ingrediente ricetta
struct ingredienteRicetta {
  char nome[MAX_CHAR_NOME_INGREDIENTE];
  int grammi;
  linkIngredienteRicetta next;
};

//struct wrapper ingredienti ricetta
struct ingredientiRicetta {
  linkIngredienteRicetta head;
  linkIngredienteRicetta tail;
  int tot_ingredienti;
};

//Acquisizione ingredienti ricetta
linkIngredientiRicetta generazioneIngredientiRicetta(FILE *fp_ricette) {
  int i;
  linkIngredienteRicetta new_ingrediente_ricetta=(linkIngredienteRicetta)malloc(sizeof(*new_ingrediente_ricetta));
  linkIngredientiRicetta ingredienti_ricetta=(linkIngredientiRicetta)malloc(sizeof(*ingredienti_ricetta));

  ingredienti_ricetta->head=ingredienti_ricetta->tail=NULL;

  if (fp_ricette==stdin)
    printf("Numero ingredienti: ");
  fscanf(fp_ricette, "%d", &ingredienti_ricetta->tot_ingredienti);

  for (i = 0; i < ingredienti_ricetta->tot_ingredienti; i++) {
    if (fp_ricette==stdin)
      printf("Nome ingrediente: ");
    fscanf(fp_ricette, "%s", new_ingrediente_ricetta->nome);
    if (fp_ricette==stdin)
      printf("Grammi ingrediente: ");
    fscanf(fp_ricette, "%d", &new_ingrediente_ricetta->grammi);
    new_ingrediente_ricetta->next=NULL;

    listInsTailIngredienteRicetta(ingredienti_ricetta, new_ingrediente_ricetta);
  }

  free(new_ingrediente_ricetta);

  return(ingredienti_ricetta);
}

//Inserimenti in coda
void listInsTailIngredienteRicetta(linkIngredientiRicetta ingredienti_ricetta, linkIngredienteRicetta new_ingrediente_ricetta) {
  if ((ingredienti_ricetta->head)==NULL) {
    ingredienti_ricetta->head=ingredienti_ricetta->tail=newNodeIngredienteRicetta(new_ingrediente_ricetta);
    return;
  }

  ingredienti_ricetta->tail->next=newNodeIngredienteRicetta(new_ingrediente_ricetta);
  ingredienti_ricetta->tail=ingredienti_ricetta->tail->next;

  return;
}

//Creazione nodo in coda
linkIngredienteRicetta newNodeIngredienteRicetta(linkIngredienteRicetta new_ingrediente_ricetta) {
  linkIngredienteRicetta x=(linkIngredienteRicetta)malloc(sizeof(*x));
  if (x==NULL)
    return(NULL);

  strcpy(x->nome, new_ingrediente_ricetta->nome);
  x->grammi=new_ingrediente_ricetta->grammi;
  x->next=new_ingrediente_ricetta->next;

  return(x);
}

//Ricerca ingrediente ricetta
linkIngredienteRicetta ricercaIngredienteRicetta(linkIngredientiRicetta ingredienti_ricetta, char nome_ingrediente[MAX_CHAR_NOME_INGREDIENTE]) {
  linkIngredienteRicetta x=ingredienti_ricetta->head;
  int i;

  for (i = 0; i < ingredienti_ricetta->tot_ingredienti; i++) {
    if (!strcmp(nome_ingrediente, x->nome))
      break;

    x=x->next;
  }

  return(x);
}

//Stampa ingredienti ricetta
void stampaIngredientiRicetta(linkIngredientiRicetta ingredienti_ricetta) {
  linkIngredienteRicetta x=ingredienti_ricetta->head;
  int i;

  printf("Elenco ingredienti:\n");
  for (i = 0; i < ingredienti_ricetta->tot_ingredienti; i++) {
    printf("- Nome: %s - Grammi: %d\n", x->nome, x->grammi);
    x=x->next;
  }

  return;
}

//Free ingredienti ricetta e struct wrapper
void freeIngredientiRicetta(linkIngredientiRicetta ingredienti_ricetta) {
  linkIngredienteRicetta x=ingredienti_ricetta->head, x_next;
  int i;

  for (i = 0; i < ingredienti_ricetta->tot_ingredienti; i++) {
    x_next=x->next;
    free(x);
    x=x_next;
  }

  free(ingredienti_ricetta);

  return;
}
