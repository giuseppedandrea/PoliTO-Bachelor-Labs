#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

typedef struct node *link;

struct node {
  int x, y;
  float dist_origin;
  link next;
};

int readCoord(int *x, int *y);
link sortListIns(link h, int x_, int y_);
link newNode(int x_, int y_, float dist_origin_, link next);
void listRevTravR(link h);
void freeNode(link root);

int main(int argc, char const *argv[]) {
  int x, y;
  link head=NULL;

  //Acquisizione coordinate e inserimento in lista ordinata
  while(readCoord(&x, &y))
    head=sortListIns(head, x, y);

  //Stampa lista ordinata
  listRevTravR(head);

  //Free albero
  freeNode(head);

  return(0);
}

int readCoord(int *x, int *y) {
  printf("Inserire coordinate x e y (0 0 per terminare): ");
  scanf("%d %d", x, y);

  if((*x)==0 && (*y)==0)
    return(0);
  else
    return(1);
}

link sortListIns(link h, int x_, int y_) {
  link i, p;
  float dist_origin_=(float)(sqrt((double)((x_*x_)+(y_*y_))));

  if (h==NULL || dist_origin_<(h->dist_origin))
    return(newNode(x_, y_, dist_origin_, h));
  for (i=h->next, p=h; i!=NULL && dist_origin_>(i->dist_origin); p=i, i=i->next);
  p->next = newNode(x_, y_, dist_origin_, i);

  return(h);
}

link newNode(int x_, int y_, float dist_origin_, link next) {
  link i=(link)malloc(sizeof(*i));

  if (i==NULL)
    return(NULL);
  else {
    i->x=x_;
    i->y=y_;
    i->dist_origin=dist_origin_;
    i->next = next;
  }

  return(i);
}

void listRevTravR(link h) {
  if(h==NULL)
    return;

  printf("x: %d y: %d dist: %.2f\n", h->x, h->y, h->dist_origin);
  listRevTravR(h->next);

  return;
}

void freeNode(link root) {
  if(root==NULL)
    return;
  freeNode(root->next);
  free(root);

  return;
}
