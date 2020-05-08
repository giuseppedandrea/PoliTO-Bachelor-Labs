#ifndef INGREDIENTI_H
#define INGREDIENTI_H

#include <stdio.h>

#define MAX_CHAR_NOME_INGREDIENTE 255+1
#define NOME_FILE_INGREDIENTI "ingredienti.txt"

//struct wrapper ingredienti
typedef struct ingredienti *linkIngredienti;

//struct ingrediente
typedef struct ingrediente *linkIngrediente;

//Acquisizione ingredienti
linkIngredienti generazioneIngredienti(void);

//Ricerca ingredienti
int ricercaIngrediente(linkIngredienti ingredienti, char nome_ingrediente[MAX_CHAR_NOME_INGREDIENTE]);

//Stampa ingredienti
void stampaIngredienti(linkIngredienti ingredienti);

//Stampa ingrediente
void stampaIngrediente(linkIngredienti ingredienti);

//Printf ingrediente
void printfIngrediente(linkIngrediente ingrediente, int dettagli);

//Free ingredienti
void freeIngredienti(linkIngredienti ingredienti);

//struct ingrediente ricetta
typedef struct ingredienteRicetta *linkIngredienteRicetta;

//struct wrapper ingredienti ricetta
typedef struct ingredientiRicetta *linkIngredientiRicetta;

//Acquisizione ingredienti ricetta
linkIngredientiRicetta generazioneIngredientiRicetta(FILE *fp_ricette);

//Inserimenti in coda
void listInsTailIngredienteRicetta(linkIngredientiRicetta ingredienti_ricetta, linkIngredienteRicetta new_ingrediente_ricetta);

//Creazione nodo in coda
linkIngredienteRicetta newNodeIngredienteRicetta(linkIngredienteRicetta new_ingrediente_ricetta);

//Ricerca ingrediente ricetta
linkIngredienteRicetta ricercaIngredienteRicetta(linkIngredientiRicetta ingredienti_ricetta, char nome_ingrediente[MAX_CHAR_NOME_INGREDIENTE]);

//Stampa ingredienti ricetta
void stampaIngredientiRicetta(linkIngredientiRicetta ingredienti_ricetta);

//Free ingredienti ricetta e struct wrapper
void freeIngredientiRicetta(linkIngredientiRicetta ingredienti_ricetta);

#endif
