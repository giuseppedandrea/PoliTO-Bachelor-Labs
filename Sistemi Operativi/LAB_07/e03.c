#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define MAX_NAME 256+1

typedef struct argThread {
  int index;
  char *nameIn;
  int n;
  int *vet;
} argThread_t;

void *routineThread(void *arg);

int main (int argc, char *argv[]) {
  FILE *fp_out;
  char **nameIn, *nameOut;
  int i, j, k, n, q, digits, len, *tmp, *res;
  void *ret;
  pthread_t *tid;
  argThread_t *arg;

  setbuf(stdout, 0);

  if (argc != 4) {
    fprintf(stdout, "Usage: %s <n> <nameInN> <nameOut>\n", argv[0]);
    exit(1);
  }

  n=atoi(argv[1]);

  nameIn=(char **)malloc(n*sizeof(char *));
  for (i=0; i<n; i++) {
    q=i+1;
    digits=0;
    while (q != 0) {
      q/=10;
      digits++;
    }
    nameIn[i]=(char *)malloc((strlen(argv[2])+digits+strlen(".txt")+1)*sizeof(char));
    sprintf(nameIn[i], "%s%d.txt", argv[2], i+1);
  }
  
  tid=(pthread_t *)malloc(n*sizeof(pthread_t));
  arg=(argThread_t *)malloc(n*sizeof(argThread_t));
  for (i=0; i<n; i++) {
    arg[i].index=i+1;
    arg[i].nameIn=nameIn[i];
    pthread_create(&tid[i], NULL, routineThread, (void *)&arg[i]);
  }

  for (i=0; i<n; i++) {
    pthread_join(tid[i], &ret);
 
    //printf("thread=%d exit=%d\n", i, *(int *)&ret);
    
    if (i == 0) {
      len=arg[i].n;
      res=(int *)malloc(len*sizeof(int));
      for (j=0; j<len; j++) {
        res[j]=arg[i].vet[j];
      }
    } else {
      j=0;
      k=0;
      tmp=(int *)malloc((len+(arg[i].n))*sizeof(int));
      while (j<len || k<(arg[i].n)) {
        if (j>=len) {
          tmp[j+k]=arg[i].vet[k];
          k++;
        } else if (k>=(arg[i].n)) {
          tmp[j+k]=res[j];
          j++;
        } else {
          if (res[j]<arg[i].vet[k]) {
            tmp[j+k]=res[j];
            j++;
          } else {
            tmp[j+k]=arg[i].vet[k];
            k++;
          }
        }
      }
      free(res);
      len+=arg[i].n;
      res=(int *)malloc(len*sizeof(int));
      for (j=0; j<len; j++) {
        res[j]=tmp[j];
      }
      free(tmp);
    }
  }

  nameOut=(char *)malloc((strlen(argv[3])+strlen(".txt")+1)*sizeof(char));
  sprintf(nameOut, "%s.txt", argv[3]);
 
  if ((fp_out=fopen(nameOut, "w")) == NULL) {
    printf("Error in opening %s\n", nameOut);
    exit(1);
  }

  fprintf(stdout, "Ordered Merge (Length=%d):\n", len);
  for (i=0; i<len; i++) {
    fprintf(stdout, "%d\n", res[i]);
  }

  fclose(fp_out);

  for (i=0; i<n; i++) {
    free(nameIn[i]);
    free(arg[i].vet);
  }
  free(nameIn);
  free(nameOut);
  free(tid);
  free(arg);

  return 0;
}

int cmp(const void *a, const void*b) {
  return ((*(int *)a)-(*(int *)b));
}

void *routineThread(void *arg) {
  FILE *fp_in;  
  argThread_t *_arg=(argThread_t *)arg;
  int i;

  if ((fp_in=fopen(_arg->nameIn, "r")) == NULL) {
    printf("Error in opening %s\n", _arg->nameIn);
    pthread_exit((void *)1);
  }
 
  fscanf(fp_in, "%d", &(_arg->n));

  //printf("thread=%d n=%d\n", _arg->index, _arg->n);

  _arg->vet=(int *)malloc((_arg->n)*sizeof(int));
  for (i=0; i<(_arg->n); i++) {
    fscanf(fp_in, "%d", &(_arg->vet[i]));
  }

  qsort((void *)(_arg->vet), (_arg->n), sizeof(int), cmp);

  for (i=0; i<(_arg->n); i++) {
    //printf("thread=%d vet[%d]=%d\n", _arg->index, i, _arg->vet[i]);
  }

  fclose(fp_in);

  pthread_exit((void *)0);
}
