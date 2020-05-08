#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define MAX_NAME 256+1

typedef struct argThread {
  int index;
  char *nameA;
  char *nameB;
} argThread_t;

void *routineThread(void *arg);

int main (int argc, char *argv[]) {
  char **nameA, **nameB;
  int i, n, tmp, digits;
  pthread_t *tid;
  argThread_t *arg;

  if (argc != 4) {
    fprintf(stdout, "Usage: %s <n> <strA> <strB>\n", argv[0]);
    exit(1);
  }

  n=atoi(argv[1]);

  nameA=(char **)malloc(n*sizeof(char *));
  nameB=(char **)malloc(n*sizeof(char *));
  for (i=0; i<n; i++) {
    tmp=i+1;
    digits=0;
    while (tmp != 0) {
      tmp/=10;
      digits++;
    }
    nameA[i]=(char *)malloc((strlen(argv[2])+digits+strlen(".txt")+1)*sizeof(char));
    sprintf(nameA[i], "%s%d.txt", argv[2], i+1);
    nameB[i]=(char *)malloc((strlen(argv[3])+digits+strlen(".txt")+1)*sizeof(char));
    sprintf(nameB[i], "%s%d.txt", argv[3], i+1);
  }

  tid=(pthread_t *)malloc(n*sizeof(pthread_t));
  arg=(argThread_t *)malloc(n*sizeof(argThread_t));
  for (i=0; i<n; i++) {
    arg[i].index=i+1;
    arg[i].nameA=nameA[i];
    arg[i].nameB=nameB[i];
    pthread_create(&tid[i], NULL, routineThread, (void *)&arg[i]);
  }

  for (i=0; i<n; i++) {
    pthread_join(tid[i], NULL);
  }

  for (i=0; i<n; i++) {
    free(nameA[i]);
    free(nameB[i]);
  }
  free(nameA);
  free(nameB);
  free(tid);
  free(arg);

  return 0;
}

int cmp(const void *a, const void*b) {
  return ((*(int *)a)-(*(int *)b));
}

void *routineThread(void *arg) {
  FILE *fp_in, *fp_out;  
  argThread_t *_arg=(argThread_t *)arg;
  int i, n, *vet;

  printf("%d\n", _arg->index);

  if ((fp_in=fopen(_arg->nameA, "r")) == NULL ) {
    printf("Error in opening %s\n", _arg->nameA);
    pthread_exit((void *)1);
  }
  if ((fp_out=fopen(_arg->nameB, "w")) == NULL ) {
    printf("Error in opening %s\n", _arg->nameB);
    pthread_exit((void *)1);
  }
  
  fscanf(fp_in, "%d", &n);

  vet=(int *)malloc(n*sizeof(int));
  for (i=0; i<n; i++) {
    fscanf(fp_in, "%d", &vet[i]);
  }

  qsort((void *)vet, n, sizeof(int), cmp);
  
  for (i=0; i<n; i++) {
    fprintf(fp_out, "%d\n", vet[i]);
  }

  free(vet);

  fclose(fp_in);
  fclose(fp_out);

  pthread_exit((void *)0);
}
