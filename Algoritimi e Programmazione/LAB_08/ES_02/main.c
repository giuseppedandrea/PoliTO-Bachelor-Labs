#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ingredienti.h"
#include "ricette.h"

#define MAX_CHAR_COMANDO 40+1
#define MAX_CHAR_NOME_RICETTA 255+1

#define COMANDO_0 "help"
#define COMANDO_1 "stampa_ricetta"
#define COMANDO_2 "stampa_ricette"
#define COMANDO_3 "stampa_ingrediente"
#define COMANDO_4 "stampa_ingredienti"
#define COMANDO_5 "calcolo_costo"
#define COMANDO_6 "calcolo_calorie"
#define COMANDO_7 "ricerca_ingrediente_ricette"
#define COMANDO_8 "inserisci_ricetta"
#define COMANDO_9 "fine"

typedef enum {c_help, c_stampa_ricetta, c_stampa_ricette, c_stampa_ingrediente, c_stampa_ingredienti, c_calcolo_costo, c_calcolo_calorie, c_ricerca_ingrediente_ricette, c_inserisci_ricetta, c_fine, c_err} comandoMenu;
char elenco_comandi[c_err][MAX_CHAR_COMANDO]={COMANDO_0, COMANDO_1, COMANDO_2, COMANDO_3, COMANDO_4, COMANDO_5, COMANDO_6, COMANDO_7, COMANDO_8, COMANDO_9};

void elaboraComando(linkIngredienti ingredienti, linkRicette ricette);
comandoMenu leggiComando(void);
void visualizzaHelp(void);

int main(int argc, char const *argv[]) {
  linkIngredienti ingredienti;
  linkRicette ricette;

  ingredienti=generazioneIngredienti();
  ricette=generazioneRicette();

  elaboraComando(ingredienti, ricette);

  freeIngredienti(ingredienti);
  freeRicette(ricette);

  return(0);
}

void elaboraComando(linkIngredienti ingredienti, linkRicette ricette) {

  int continua=1;
  comandoMenu codice_comando;

  while (continua) {
    codice_comando=leggiComando();

    switch (codice_comando) {
      case c_help:
        visualizzaHelp();
        break;
      case c_stampa_ricetta:
        stampaRicetta(ricette);
        break;
      case c_stampa_ricette:
        stampaRicette(ricette);
        break;
      case c_stampa_ingrediente:
        stampaIngrediente(ingredienti);
        break;
      case c_stampa_ingredienti:
        stampaIngredienti(ingredienti);
        break;
      case c_calcolo_costo:
        calcoloCosto(ricette, ingredienti);
        break;
      case c_calcolo_calorie:
        calcoloCalorie(ricette, ingredienti);
        break;
      case c_ricerca_ingrediente_ricette:
        ricercaIngredienteRicette(ricette, ingredienti);
        break;
      case c_inserisci_ricetta:
        inserisciRicetta(ricette);
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

comandoMenu leggiComando(void) {
  int i;
  char comando[MAX_CHAR_COMANDO];

  printf("Inserisci comando (lista comandi con \"help\"): ");
  scanf("%s", comando);

  for (i = 0; i < c_err; i++)
    if (!strcmp(comando, elenco_comandi[i]))
      break;

  return((comandoMenu)i);
}

void visualizzaHelp(void) {
  int i;

  printf("Elenco comandi:\n");
  for (i = 0; i < c_err; i++)
    printf("- %s\n", elenco_comandi[i]);

  return;
}
