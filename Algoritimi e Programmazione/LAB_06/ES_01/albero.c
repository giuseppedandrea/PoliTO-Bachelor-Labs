#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXS 11 /* 10 + 1 per '\0' */

// Definizione delle strutture dati usate
typedef struct nodo* link;

struct nodo {
  char val[MAXS];
  link left;
  link right;
};

// Prototipi delle funzioni di utilità
link new_nodo(char *val);
link leggi_nodo(FILE *in);
link leggi_albero(char *filename);
void display_albero(link root);
void libera_albero(link root);

// Prototipi delle funzioni da implementare
int contaCompleti(link n, int L1, int L2);
void checkLivello(link n, int *conta, int *l, int L1, int L2);
int distanza(link n, char *K1, char *K2);
link nodoComune(link n, char *K1, char *K2);
int distanzaNodo(link n, char *K);

int main(int argc, char **argv) {
  int l1, l2, n_nodi, n_archi;
  char k1[MAXS], k2[MAXS];
  link root;
  root = leggi_albero(argv[1]);
  printf("Lista nodi: \n");
  display_albero(root);

  // Invocazione delle funzioni richieste

  printf("\n- Conteggio numero nodi con 2 figli tra due livelli\n");
  printf("Inserire primo livello: ");
  scanf("%d", &l1);
  printf("Inserire secondo livello: ");
  scanf("%d", &l2);
  n_nodi=contaCompleti(root, l1, l2);
  printf("Ci sono %d nodi con 2 figli tra i livelli %d e %d\n", n_nodi, l1, l2);

  printf("\n- Conteggio numero di archi che separano due nodi\n");
  printf("Inserire primo nodo: ");
  scanf("%s", k1);
  printf("Inserire secondo nodo: ");
  scanf("%s", k2);
  n_archi=distanza(root, k1, k2);
  printf("Ci sono %d archi tra i nodi %s e %s\n", n_archi, k1, k2);

  libera_albero(root);
  return 0;
}

// Implementazione delle funzioni di utilità

link new_nodo(char *val) {
    link n = (link)malloc(1*sizeof(*n));
    strcpy(n->val,val);
    n->left = NULL;
    n->right = NULL;
    return n;
};

link leggi_nodo(FILE *in) {
  char val[MAXS];
  int l, r;
  if (fscanf(in, "%s %d %d", val, &l, &r) != 3) return NULL;
  link n = new_nodo(val);
  if (l!=0) n->left = leggi_nodo(in);
  if (r!=0) n->right = leggi_nodo(in);
  return n;
}

link leggi_albero(char *filename) {
  FILE *in;
  in = fopen(filename, "r");
  link root = leggi_nodo(in);
  fclose(in);
  return root;
}

void display_albero(link root) {
    if (root == NULL) return;
    printf("nodo %s\n", root->val);
    display_albero(root->left);
    display_albero(root->right);
}

void libera_albero(link root) {
    if (root == NULL) return;
    libera_albero(root->left);
    libera_albero(root->right);
    free(root);
}

// Implementazione delle funzioni da aggiungere

int contaCompleti(link n, int L1, int L2) {
  int l=0, conta=0;

  checkLivello(n, &conta, &l, L1, L2);

  return(conta);
}

void checkLivello(link n, int *conta, int *l, int L1, int L2) {
  if (n == NULL) {
    (*l)--;
    return;
  }

  if((*l)>=L1 && (*l)<=L2)
    if (n->left != NULL && n->right != NULL)
      (*conta)++;

  (*l)++;
  checkLivello(n->left, conta, l, L1, L2);
  (*l)++;
  checkLivello(n->right, conta, l, L1, L2);

  (*l)--;
  return;
}

int distanza(link n, char *K1, char *K2) {
  int distanza_K1, distanza_K2;

  // Trovo il piu' piccolo nodo in comune
  n=nodoComune(n, K1, K2);

  distanza_K1=distanzaNodo(n, K1);

  distanza_K2=distanzaNodo(n, K2);

	return(distanza_K1+distanza_K2);
}

link nodoComune(link n, char *K1, char *K2) {
    if (n == NULL)
      return(NULL);

    // Se K1 e K2 sono piu' piccoli della radice, allora il nodo comune e' a sinistra
    if (strcmp(n->val, K1)>0 && strcmp(n->val, K2)>0)
        return(nodoComune(n->left, K1, K2));

    // Se K1 e K2 sono piu' grandi della radice, allora il nodo comune e' a destra
    if (strcmp(n->val, K1)<0 && strcmp(n->val, K2)<0)
        return(nodoComune(n->right, K1, K2));

    return(n);
}

int distanzaNodo(link n, char *K) {
  if (n == NULL || strcmp(n->val, K)==0)
    return(0);

  if (strcmp(n->val, K)>0)
    return(1+distanzaNodo(n->left, K));
  else
    return(1+distanzaNodo(n->right, K));
}
