#ifndef INGREDIENTI_H
#define INGREDIENTI_H

#define MAX_CHAR_NOME_INGREDIENTE 255+1
#define NOME_FILE_INGREDIENTI "ingredienti.txt"

//struct ingrediente
typedef struct ingrediente *linkIngrediente;

struct ingrediente {
  char nome[MAX_CHAR_NOME_INGREDIENTE];
  float costo;
  float calorie;
  linkIngrediente next;
};

//struct wrapper ingredienti
typedef struct ingredienti *linkIngredienti;

struct ingredienti {
  linkIngrediente head;
  linkIngrediente tail;
  int tot_ingredienti;
};

//Acquisizione ingredienti
linkIngredienti creazioneListIngredienti(void);

//Inserimenti in coda
void listInsTail(linkIngredienti list_ingredienti, linkIngrediente new_ingrediente);

//Creazione nodo in coda
linkIngrediente newNode(linkIngrediente new_ingrediente);

//Ricerca ingredienti
linkIngrediente ricercaIngrediente(linkIngredienti list_ingredienti, char str[MAX_CHAR_NOME_INGREDIENTE]);

//Stampa ingredienti
void stampaIngredienti(linkIngredienti list_ingredienti);

//Free lista ingredienti e struct wrapper
void freeListIngredienti(linkIngredienti list_ingredienti);

#endif
