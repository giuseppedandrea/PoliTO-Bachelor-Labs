#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include "Item.h"
#include "PQ.h"

#define MAXM 30+1

typedef enum {e_help, e_display, e_insert, e_delete, e_match, e_load, e_save, e_exit, e_err} enum_menu;
char c_menu[e_err][MAXM]={"help", "display", "insert", "delete", "match", "load", "save", "exit"};

void showMenu(void);
enum_menu selectMenu(void);
void elaborate(void);
void matchGenerate(void);
void matchWinner(Item winner, Item loser);

int main(int argc, char const *argv[]) {
  srand((unsigned int)time(NULL));

  PQinit();

  elaborate();

  return(0);
}

void showMenu(void) {
  int i;

  printf("Commands list:\n");
  for (i = 0; i < e_err; i++)
    printf("- %s\n", c_menu[i]);

  return;
}

enum_menu selectMenu(void) {
  int i;
  char command[MAXM];

  printf("Insert command: ");
  scanf("%s", command);

  for (i = 0; i < e_err; i++)
    if (!strcmp(command, c_menu[i]))
      break;

  return((enum_menu)i);
}

void elaborate(void) {
  int repeat=1;
  enum_menu command;

  while (repeat) {
    command=selectMenu();

    switch (command) {
      case e_help:
        showMenu();
        break;
      case e_display:
        PQdisplay(stdout);
        break;
      case e_insert:
        PQinsert(ITEMnew());
        break;
      case e_delete:
        PQdelete(ITEMnew());
        break;
      case e_match:
        matchGenerate();
        break;
      case e_load:
        PQload();
        break;
      case e_save:
        PQsave();
        break;
      case e_exit:
        repeat=0;
        break;
      case e_err:
      default:
        printf("Wrong command!\n");
        showMenu();
        break;
    }

    printf("\n");
  }

  return;
}

void matchGenerate(void) {
  Item player_1, player_2;
  int result;

  if (PQcount()<2) {
    printf("Minimun 2 players\n");
    return;
  }

  player_1=PQextractMin();
  player_2=PQextractMin();

  printf("%s vs %s\n", NAMEget(player_1), NAMEget(player_2));

  result=rand()<(RAND_MAX/2);

  if (result)
    matchWinner(player_1, player_2);
  else
    matchWinner(player_2, player_1);

  if (KEYget(player_1)<=0)
    printf("%s eliminated\n", NAMEget(player_1));
  else
    PQinsert(player_1);

  if (KEYget(player_2)<=0)
    printf("%s eliminated\n", NAMEget(player_2));
  else
    PQinsert(player_2);

  return;
}

void matchWinner(Item winner, Item loser) {
  printf("Win: %s\n", NAMEget(winner));
  KEYset(winner, KEYget(winner)+(KEYget(loser)*0.25));
  KEYset(loser, KEYget(loser)-(KEYget(loser)*0.25));

  return;
}
