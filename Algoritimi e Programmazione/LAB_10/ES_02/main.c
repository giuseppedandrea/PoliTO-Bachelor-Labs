#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define DBG 1

#define MAXC 20+1

typedef struct equip_t {
  char nome[MAXC], categoria[MAXC];
  int dim1, dim2, utilita;
} *Equip;

typedef struct equips_t {
  int n;
  Equip equip;
} Equips;

Equips equipsInit(char const *file_name);

int main(int argc, char const *argv[]) {
  int inv1, inv2;
  Equips equips;

  if (argc != 2) {
    printf("Example: %s <input_file>\n", argv[0]);
    return(EXIT_FAILURE);
  }

  equips=equipsInit(argv[1]);

#if DBG
// Show equips
  int i;
  printf("N: %d\n", equips.n);
  for (i = 0; i < equips.n; i++) {
    printf("%s %s %d %d %d\n", equips.equip[i].nome, equips.equip[i].categoria, equips.equip[i].dim1, equips.equip[i].dim2, equips.equip[i].utilita);
  }
  printf("\n");
#endif

  printf("inv1: ");
  scanf("%d", &inv1);
  printf("inv2: ");
  scanf("%d", &inv2);

  return(0);
}

Equips equipsInit(char const *file_name) {
  Equips equips;
  FILE *fp_in;
  int i;
  char nome[MAXC], categoria[MAXC];

  if ((fp_in=fopen(file_name, "r")) == NULL) {
    printf("File error!\n");
    exit(EXIT_FAILURE);
  }

  fscanf(fp_in, "%d", &equips.n);

  equips.equip=(Equip)malloc(equips.n*sizeof(*equips.equip));

  for (i = 0; i < equips.n; i++) {
    fscanf(fp_in, "%s %s %d %d %d", nome, categoria, &equips.equip[i].dim1, &equips.equip[i].dim2, &equips.equip[i].utilita);
    strcpy(equips.equip[i].nome, nome);
    strcpy(equips.equip[i].categoria, categoria);
  }

  return(equips);
}
