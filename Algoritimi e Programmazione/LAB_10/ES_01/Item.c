#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Item.h"

struct item {
  int cardId;
  int *skilift_time;
};

Item ITEMnew(Key key, Len len) {
  int i;
  Item tmp=(Item)malloc(sizeof(struct item));

  if (tmp == NULL)
    return(ITEMsetVoid());

  tmp->skilift_time=(int*)malloc(len*sizeof(*tmp->skilift_time));

  for (i = 0; i < len; i++)
    tmp->skilift_time[i]=-1;

  ITEMset(tmp, key);

  return(tmp);
}

Item ITEMsetVoid(void) {
  Item tmp=(Item)malloc(sizeof(struct item));
  if (tmp != NULL)
    ITEMset(tmp, -1);

  return(tmp);
}

int ITEMcheckVoid(Item data) {
  Key k1, k2=-1;
  k1=KEYget(data);
  if (KEYcompare(k1,k2)==0)
    return(1);
  else
    return(0);
}

void ITEMset(Item data, Key key) {
  data->cardId=key;
  return;
}

int ITEMequal(Item data1, Item data2) {
  Key k1 = KEYget(data1), k2 = KEYget(data2);
  if (KEYcompare(k1, k2) == 0)
    return(1);
  else
    return(0);
}

int ITEMgreater(Item data1, Item data2) {
  Key k1 = KEYget(data1), k2 = KEYget(data2);
  if (KEYcompare(k1, k2) == 1)
    return(1);
  else
    return(0);
}

int ITEMgreaterEqual(Item data1, Item data2) {
  Key k1 = KEYget(data1), k2 = KEYget(data2);
  if (KEYcompare(k1, k2) == 1 || KEYcompare(k1, k2) == 0)
    return(1);
  else
    return(0);
}

int ITEMless(Item data1, Item data2) {
  Key k1 = KEYget(data1), k2 = KEYget(data2);
  if (KEYcompare(k1, k2) == -1)
    return(1);
  else
    return(0);
}

int ITEMlessEqual(Item data1, Item data2) {
  Key k1 = KEYget(data1), k2 = KEYget(data2);
  if (KEYcompare(k1, k2) == -1 || KEYcompare(k1, k2) == 0)
    return(1);
  else
    return(0);
}

int KEYcompare(Key k1, Key k2) {
  if (k1 < k2)
    return(-1);
  else if (k1 == k2)
    return(0);
  else
    return(1);
}

void ITEMdisplay(Item data, FILE *output) {
  fprintf(output, "CardId: %d\n", KEYget(data));
  return;
}

Key KEYget(Item data) {
  return(data->cardId);
}

void KEYset(Item data, Key key) {
  data->cardId=key;
  return;
}

Key TIMEget(Item data, Key key) {
  return(data->skilift_time[key]);
}

void TIMEset(Item data, Key k1, Key k2) {
  data->skilift_time[k1]=k2;
  return;
}
