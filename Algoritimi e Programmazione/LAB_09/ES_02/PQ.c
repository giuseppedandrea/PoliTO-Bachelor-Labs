#include <stdlib.h>
#include <stdio.h>
#include "Item.h"
#include "PQ.h"

typedef struct PQnode *link;

struct PQnode {
  Item val;
  link next;
};

static link head;

static link NEW(Item val, link next) {
  link x=(link)malloc(sizeof(*x)) ;
  x->val=val;
  x->next=next;
  return(x);
}

void PQinit(void) {
  head=NULL;
  return;
}

int PQempty(void) {
  return(head == NULL);
}

void PQinsert (Item val) {
  head=NEW(val, head);

  return;
}

void PQdelete (Item val) {
  link x, p;

  if (PQempty()) {
    printf("PQ empty\n");
    return;
  }

  for (x=head, p=NULL; x!=NULL; p=x, x=x->next) {
    if (NAMEequal(val, x->val)){
      if (x==head)
        head=x->next;
      else
        p->next=x->next;
      free(x);
      break;
    }
  }

  if (x==NULL)
    printf("Wrong name! No delete\n");

  return;
}

int PQcount(void) {
  link x;
  int n;

  for (x=head, n=0; x!=NULL; x=x->next)
    n++;

  return(n);
}

Item PQextractMin(void) {
  Item min=ITEMsetVoid();
  link x, x_min, p, p_min, tmp;

  if (PQempty()) {
    printf("PQ empty\n");
    return(ITEMsetVoid());
  }

  for (x=head, p=NULL; x!=NULL; p=x, x=x->next) {
    if (ITEMless(x->val, min)) {
      min=x->val;
      x_min=x;
      p_min=p;
    }
  }

  if (x_min==head) { // Estrazione in testa
    tmp=head;
    head=head->next;
    free(tmp);
  } else { // Estrazione in lista
    tmp=p_min->next;
    p_min->next=tmp->next;
    free(tmp);
  }

  return(min);
}

void PQdisplay(FILE *output) {
  link x;

  if (PQempty()) {
    printf("PQ empty\n");
    return;
  }

  for (x=head; x!=NULL; x=x->next)
    ITEMdisplay(x->val, output);

  return;
}

void PQload(void) {
  FILE *fp_in;
  char filename_in[MAXF], name[MAXC];
  float points;
  Item val;

  printf("Input filename: ");
  scanf("%s", filename_in);

  if ((fp_in=fopen(filename_in, "r"))==NULL) {
    printf("File not exist!\n");
    return;
  }

  while (fscanf(fp_in, " Name: %s - Points: %f", name, &points)==2) {
    val=ITEMsetVoid();
    ITEMset(val, name, points);
    PQinsert(val);
  }

  fclose(fp_in);

  return;
}

void PQsave(void) {
  FILE *fp_out;
  char filename_out[MAXF];

  printf("Output filename: ");
  scanf("%s", filename_out);

  if ((fp_out=fopen(filename_out, "w"))==NULL) {
    printf("File not exist!\n");
    return;
  }

  PQdisplay(fp_out);

  fclose(fp_out);

  return;
}
