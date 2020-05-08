#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ingredienti.h"

//Acquisizione ingredienti
linkIngredienti creazioneListIngredienti() {
  int i;
  FILE *fp_ingredienti;
  linkIngrediente new_ingrediente=(linkIngrediente)malloc(sizeof(*new_ingrediente));
  linkIngredienti list_ingredienti=(linkIngredienti)malloc(sizeof(*list_ingredienti));

  list_ingredienti->head=list_ingredienti->tail=NULL;

  if ((fp_ingredienti=fopen(NOME_FILE_INGREDIENTI, "r"))==NULL) {
    printf("Errore nell'apertura del file!\n");
    exit(EXIT_FAILURE);
  }

  fscanf(fp_ingredienti, "%d", &list_ingredienti->tot_ingredienti);

  for (i = 0; i < list_ingredienti->tot_ingredienti; i++) {
    fscanf(fp_ingredienti, "%s %f %f", new_ingrediente->nome, &new_ingrediente->costo, &new_ingrediente->calorie);
    new_ingrediente->next=NULL;

    listInsTail(list_ingredienti, new_ingrediente);
  }

  free(new_ingrediente);

  fclose(fp_ingredienti);

  return(list_ingredienti);
}

//Inserimenti in coda
void listInsTail(linkIngredienti list_ingredienti, linkIngrediente new_ingrediente) {
  if ((list_ingredienti->head)==NULL) {
    list_ingredienti->head=list_ingredienti->tail=newNode(new_ingrediente);
    return;
  }

  list_ingredienti->tail->next=newNode(new_ingrediente);
  list_ingredienti->tail=list_ingredienti->tail->next;

  return;
}

//Creazione nodo in coda
linkIngrediente newNode(linkIngrediente new_ingrediente) {
  linkIngrediente x=(linkIngrediente)malloc(sizeof(*x));
  if (x==NULL)
    return(NULL);

  strcpy(x->nome, new_ingrediente->nome);
  x->costo=new_ingrediente->costo;
  x->calorie=new_ingrediente->calorie;
  x->next=new_ingrediente->next;

  return(x);
}

//Ricerca ingredienti
linkIngrediente ricercaIngrediente(linkIngredienti list_ingredienti, char str[MAX_CHAR_NOME_INGREDIENTE]) {
  linkIngrediente x=list_ingredienti->head;
  int i;

  for (i = 0; i < list_ingredienti->tot_ingredienti; i++) {
    if (!strcmp(str, x->nome))
      break;

    x=x->next;
  }

  return(x);
}

//Stampa ingredienti
void stampaIngredienti(linkIngredienti list_ingredienti) {
  linkIngrediente x=list_ingredienti->head;
  int i;

  printf("Elenco ingredienti:\n");
  for (i = 0; i < list_ingredienti->tot_ingredienti; i++) {
    printf("%d) Nome: %s - Costo: %.2f - Calorie: %.2f\n", i+1, x->nome, x->costo, x->calorie);

    x=x->next;
  }

  return;
}

//Free lista ingredienti e struct wrapper
void freeListIngredienti(linkIngredienti list_ingredienti) {
  linkIngrediente x=list_ingredienti->head, x_next;
  int i;

  for (i = 0; i < list_ingredienti->tot_ingredienti; i++) {
    x_next=x->next;
    free(x);
    x=x_next;
  }

  free(list_ingredienti);

  return;
}
