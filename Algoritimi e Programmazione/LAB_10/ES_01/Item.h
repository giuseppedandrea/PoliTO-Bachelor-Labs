#ifndef ITEM_H
#define ITEM_H

#include <stdio.h>

typedef struct item* Item;
typedef int Key, Len;

Item ITEMnew(Key key, Len len);
Item ITEMsetVoid(void);
int ITEMcheckVoid(Item data);
void ITEMset(Item data, Key key);
int ITEMequal(Item data1, Item data2);
int ITEMgreater(Item data1, Item data2);
int ITEMgreaterEqual(Item data1, Item data2);
int ITEMless(Item data1, Item data2);
int ITEMlessEqual(Item data1, Item data2);
int KEYcompare(Key k1, Key k2);
void ITEMdisplay(Item data, FILE *output);
Key KEYget(Item data);
void KEYset(Item data, Key key);
Key TIMEget(Item data, Key key);
void TIMEset(Item data, Key k1, Key k2);

#endif
