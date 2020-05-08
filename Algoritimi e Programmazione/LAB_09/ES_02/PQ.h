#ifndef ITEM_H_DEFINED
#define ITEM_H_DEFINED

#include <stdio.h>
#include "Item.h"

#define MAXF 15+1

typedef struct pqueue *PQ;

void PQinit(void);
int PQempty(void);
void PQinsert(Item data);
void PQdelete(Item data);
int PQcount(void);
Item PQextractMin(void);
void PQdisplay(FILE *output);
void PQload(void);
void PQsave(void);

#endif
