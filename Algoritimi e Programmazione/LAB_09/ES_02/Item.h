#ifndef PQ_H_DEFINED
#define PQ_H_DEFINED

#include <stdio.h>

#define MAXC 20+1

typedef struct item* Item;
typedef float Key;
typedef char* Name;

Item ITEMnew(void);
int ITEMcheckVoid(Item data);
Item ITEMsetVoid(void);
void ITEMset(Item data, Name name, Key key);
int ITEMequal(Item data1, Item data2);
int ITEMgreater(Item data1, Item data2);
int ITEMgreaterEqual(Item data1, Item data2);
int ITEMless(Item data1, Item data2);
int ITEMlessEqual(Item data1, Item data2);
int KEYcompare(Key k1, Key k2);
int NAMEequal(Item data1, Item data2);
int NAMEcompare(Name k1, Name k2);
void ITEMdisplay(Item data, FILE *output);
Key KEYget(Item data);
void KEYset(Item data, Key key);
Name NAMEget(Item data);

#endif
