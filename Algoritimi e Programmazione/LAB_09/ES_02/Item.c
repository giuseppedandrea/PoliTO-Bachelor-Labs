#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include "Item.h"

struct item {
  char *name;
  float points;
};

Item ITEMnew(void) {
  char name[MAXC];

  printf("Name: ");
  scanf("%s", name);

  Item tmp=(Item)malloc(sizeof(struct item));

  if (tmp == NULL)
    return(ITEMsetVoid());
  else
    ITEMset(tmp, name, 10);

  return(tmp);
}

int ITEMcheckVoid(Item data) {
  Key k1, k2=FLT_MAX;
  k1=KEYget(data);
  if (KEYcompare(k1,k2)==0)
    return(1);
  else
    return(0);
}

Item ITEMsetVoid(void) {
  char name[MAXC]="";
  Item tmp=(Item)malloc(sizeof(struct item));
  if (tmp != NULL)
    ITEMset(tmp, name, FLT_MAX);

  return(tmp);
}

void ITEMset(Item data, Name name, Key key) {
  data->name=strdup(name);
  data->points=key;

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

int NAMEequal(Item data1, Item data2) {
  Name k1 = NAMEget(data1), k2 = NAMEget(data2);
  if (NAMEcompare(k1, k2) == 0)
    return(1);
  else
    return(0);
}

int NAMEcompare(Name k1, Name k2) {
  if (strcmp(k1, k2)<0)
    return(-1);
  else if (strcmp(k1, k2)==0)
    return(0);
  else
    return(1);
}

void ITEMdisplay(Item data, FILE *output) {
  fprintf(output, "Name: %s - Points: %.2f\n", NAMEget(data), KEYget(data));
  return;
}

Key KEYget(Item data) {
  return(data->points);
}

void KEYset(Item data, Key key) {
  data->points=key;
  return;
}

Name NAMEget(Item data) {
  return(data->name);
}
