#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ingredienti.h"

#define MAX_CHAR_COMANDO 40+1
#define COMANDO_0 "help"
#define COMANDO_1 "visualizza_ingredienti"
#define COMANDO_2 "inserisci_ricetta"
#define COMANDO_3 "fine"
#define MAX_CHAR_NOME_RICETTA 255+1

typedef enum {c_help, c_visualizza_ingr, c_inserisci_ric, c_fine, c_err} comando_menu;
char elenco_comandi[c_err][MAX_CHAR_COMANDO]={COMANDO_0, COMANDO_1, COMANDO_2, COMANDO_3};

void elaboraComando(linkIngredienti list_ingredienti);
comando_menu leggiComando(void);
void visualizzaHelp(void);
void elaboraRicetta(linkIngredienti list_ingredienti);

int main(int argc, char const *argv[]) {
  linkIngredienti list_ingredienti;

  list_ingredienti=creazioneListIngredienti();

  elaboraComando(list_ingredienti);

  freeListIngredienti(list_ingredienti);

  return(0);
}

void elaboraComando(linkIngredienti list_ingredienti) {

  int continua=1;
  comando_menu codice_comando;

  while (continua) {
    codice_comando=leggiComando();

    switch (codice_comando) {
      case c_help:
        visualizzaHelp();
        break;
      case c_visualizza_ingr:
        stampaIngredienti(list_ingredienti);
        break;
      case c_inserisci_ric:
        elaboraRicetta(list_ingredienti);
        break;
      case c_fine:
        continua=0;
        break;
      case c_err:
      default:
        printf("Comando errato\n");
        visualizzaHelp();
        break;
    }

    printf("\n");
  }

  return;
}

comando_menu leggiComando(void) {
  int i;
  char comando[MAX_CHAR_COMANDO];

  printf("Inserisci comando (lista comandi con \"help\"): ");
  scanf("%s", comando);

  for (i = 0; i < c_err; i++)
    if (!strcmp(comando, elenco_comandi[i]))
      break;

  return((comando_menu)i);
}

void visualizzaHelp(void) {
  int i;

  printf("Elenco comandi:\n");
  for (i = 0; i < c_err; i++)
    printf("- %s\n", elenco_comandi[i]);

  return;
}

void elaboraRicetta(linkIngredienti list_ingredienti) {
  char nome_ricetta[MAX_CHAR_NOME_RICETTA], nome_ingrediente[MAX_CHAR_NOME_INGREDIENTE];
  int i, tempo, n_ingredienti, grammi_ingrediente;
  float tot_costo=0, tot_calorie=0;
  linkIngrediente ingrediente;

  printf("Nome ricetta: ");
  scanf("%s", nome_ricetta);
  printf("Tempo di preparazione: ");
  scanf("%d", &tempo);
  printf("Numero di ingredienti: ");
  scanf("%d", &n_ingredienti);

  for (i = 0; i < n_ingredienti; i++) {
    printf("Ingrediente %d: ", i+1);
    scanf("%s", nome_ingrediente);

    ingrediente=ricercaIngrediente(list_ingredienti, nome_ingrediente);

    if (ingrediente==NULL) {
      printf("Ingrediente inesistente!\n");
      i--;
      continue;
    }

    printf("Grammi ingrediente %d: ", i+1);
    scanf("%d", &grammi_ingrediente);

    tot_costo+=(float)grammi_ingrediente*((ingrediente->costo)/(float)1000);
    tot_calorie+=(float)grammi_ingrediente*(ingrediente->calorie);
  }

  printf("Totale costo: %.2f\n", tot_costo);
  printf("Totale calorie: %.2f\n", tot_calorie);

  return;
}
