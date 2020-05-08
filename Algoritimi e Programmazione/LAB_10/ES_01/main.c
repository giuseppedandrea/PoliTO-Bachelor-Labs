#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "Item.h"
#include "BST.h"

#define DBG 1

#define MAX_ID 10+1

typedef struct skilift_t {
  char skiliftId[MAX_ID];
  int timeInterval;
} *Skilift;

typedef struct skilifts_t {
  int n_skilift;
  Skilift skilift_list;
} Skilifts;

Skilifts skilifts;
BST sciatori;

void skiliftsInit(char const *input_file_name);
void elaborateCommand(char *skiliftId);
int authorize(int cardId, char *skiliftId, int time_now);

int main(int argc, char const *argv[]) {
  int continua=1;
  char skiliftId_[MAX_ID];

  if (argc != 2) {
    printf("Example: %s <input_file>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  skiliftsInit(argv[1]);

#if DBG
// Show "skilifts"
  int i;
  for (i = 0; i < skilifts.n_skilift; i++) {
    printf("%s %d\n", skilifts.skilift_list[i].skiliftId, skilifts.skilift_list[i].timeInterval);
  }
#endif

  sciatori=BSTinit();

  while (continua) {
    scanf("%s", skiliftId_);
    if (strcmp(skiliftId_, "stop"))
      elaborateCommand(skiliftId_);
    else
      continua=0;
  }

#if DBG
// Show "sciatori" inorder
  printf("- Inorder: \n");
  BSTsortinorder(sciatori);
#endif

  return(0);
}

void skiliftsInit(char const *input_file_name) {
  FILE *fp_in;
  int i;

  if ((fp_in=fopen(input_file_name, "r"))==NULL) {
    printf("File error!\n");
    exit(EXIT_FAILURE);
  }

  fscanf(fp_in, "%d", &skilifts.n_skilift);

  skilifts.skilift_list=(Skilift)malloc(skilifts.n_skilift*sizeof(*skilifts.skilift_list));

  for (i = 0; i < skilifts.n_skilift; i++)
    fscanf(fp_in, "%s %d", skilifts.skilift_list[i].skiliftId, &skilifts.skilift_list[i].timeInterval);

  return;
}

void elaborateCommand(char *skiliftId) {
  int cardId, time_now;

  scanf("%d %d", &cardId, &time_now);

  if (authorize(cardId, skiliftId, time_now))
    printf("Accesso autorizzato\n");
  else
    printf("Accesso negato\n");

  return;
}

int authorize(int cardId, char *skiliftId, int time_now) {
  int index, diff;
  Item item=ITEMsetVoid();

  for (index = 0; index < skilifts.n_skilift; index++)
    if (!strcmp(skilifts.skilift_list[index].skiliftId, skiliftId))
      break;

  if (skilifts.n_skilift == index) {
    printf("SkiliftId error\n");
    return(0);
  }

  item=BSTsearch(sciatori, cardId);

  if (ITEMcheckVoid(item)) {
    item=ITEMnew(cardId, skilifts.n_skilift);
    BSTinsert_leafR(sciatori, item);
    TIMEset(item, index, time_now);
    return(1);
  } else {
    if (TIMEget(item, index) == -1) {
      TIMEset(item, index, time_now);
      return(1);
    } else {
      diff=TIMEget(item, index)+skilifts.skilift_list[index].timeInterval;
      if (time_now > diff) {
        TIMEset(item, index, time_now);
        return(1);
      } else {
        return(0);
      }
    }
  }
}
