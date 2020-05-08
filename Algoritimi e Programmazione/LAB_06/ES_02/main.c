#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXC_S 50

typedef struct nodo *link;

struct nodo {
  char *sub_str;
  link next;
};

link splitString(char *str, char sep);
link listInsHead(link h, char *str);
link newNode(char *str, link next);
void listRevTravR(link h);
void freeNode(link root);

int main(int argc, char const *argv[]) {
  char string[MAXC_S+1], separatore;
  int i;
  link head;

  //Inserimento stringa
  printf("Inserire stringa:\n");
  fgets(string, MAXC_S+1, stdin);
  string[strlen(string)-1]='\0';

  //Estrapolazione separatore
  for (i = 0; isalpha(string[i]); i++);
  separatore=string[i];

  //Split della stringa in lista
  head=splitString(string, separatore);

  //Stampa della lista
  listRevTravR(head);

  //Free albero
  freeNode(head);

  return(0);
}

link splitString(char *str, char sep) {
  char *sub_str, sep_str[2]={sep, '\0'};
  link head = NULL;

  while ((sub_str=strtok(str, sep_str))!=NULL) {
    head=listInsHead(head, sub_str);
    str=NULL;
  }

  return(head);
}

link listInsHead(link h, char *str) {
  h = newNode(str,h);

  return(h);
}

link newNode(char *str, link next) {
  link x=(link)malloc(sizeof(*x));

  if (x==NULL)
    return(NULL);
  else {
    x->sub_str=strdup(str);
    x->next = next;
  }

  return(x);
}

void listRevTravR(link h) {
  if (h==NULL)
    return;

  listRevTravR(h->next);
  printf("%s\n", h->sub_str);

  return;
}

void freeNode(link root) {
  if(root==NULL)
    return;
  freeNode(root->next);
  free(root);

  return;
}
