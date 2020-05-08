#ifndef RICETTE_H
#define RICETTE_H

#include <stdio.h>

#include "ingredienti.h"

#define MAX_CHAR_NOME_RICETTA 255+1
#define NOME_FILE_RICETTE "ricette.txt"

//struct ingrediente ricetta
typedef struct ricetta *linkRicetta;

//struct wrapper ingredienti ricetta
typedef struct ricette *linkRicette;

//Acquisizione ricette
linkRicette generazioneRicette(void);

//Inserimenti in coda
void listInsTailRicetta(linkRicette ricette, linkRicetta new_ricetta, FILE *fp_ricette);

//Creazione nodo in coda
linkRicetta newNodeRicetta(linkRicetta new_ricetta, FILE *fp_ricette);

//Ricerca ricetta
linkRicetta ricercaRicetta(linkRicette ricette);

//Stampa ricette
void stampaRicette(linkRicette ricette);

//Stampa ricetta
void stampaRicetta(linkRicette ricette);

//Printf ricetta
void printfRicetta(linkRicetta ricetta, int dettagli);

//Free ricette e struct wrapper
void freeRicette(linkRicette ricette);

//Calcolo costo
void calcoloCosto(linkRicette ricette, linkIngredienti ingredienti);

//Calcolo costo ricorsiva
float calcoloCostoR(linkIngredienteRicetta ingrediente_ricetta, linkIngredienti ingredienti);

//Calcolo calorie
void calcoloCalorie(linkRicette ricette, linkIngredienti ingredienti);

//Calcolo calorie ricorsiva
float calcoloCalorieR(linkIngredienteRicetta ingrediente_ricetta, linkIngredienti ingredienti);

//Ricerca ingrediente in ricetta
void ricercaIngredienteRicette(linkRicette ricette, linkIngredienti ingredienti);

//Inserire ricetta
void inserisciRicetta(linkRicette ricette);

#endif
