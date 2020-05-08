#ifndef BST_H
#define BST_H

#include "Item.h"

typedef struct binarysearchtree *BST;

BST BSTinit(void);
int BSTcount(BST);
int BSTempty(BST);
Item BSTmin(BST);
Item BSTmax(BST);
void BSTinsert_leafI(BST, Item);
void BSTinsert_leafR(BST, Item);
void BSTinsert_root(BST, Item);
Item BSTsearch(BST, Key);
void BSTdelete(BST, Key);
Item BSTselect(BST, Key);
void BSTsortinorder(BST);
void BSTsortpreorder(BST);
void BSTsortpostorder(BST);
Item BSTsucc(BST, Key);
Item BSTpred(BST, Key);

#endif
