#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <ctype.h>

#define MAX_CHAR 100+1+1

FILE *fp_in, *fp_out;
sem_t sem_read, sem_reverse, sem_write;
char buffer[MAX_CHAR];
int end=0;

void *read(void *arg);
void *reverse(void *arg);
void *write(void *arg);

int main(int argc, char const *argv[]) {
  pthread_t tid_read, tid_reverse, tid_write;

  if (argc != 3) {
    fprintf(stderr, "Uso: %s fileIn fileOut\n", argv[0]);
    exit(1);
  }

  if ((fp_in=fopen(argv[1], "r")) == NULL) {
    fprintf(stderr, "Errore in apertura file %s\n", argv[1]);
    exit(1);
  }

  if ((fp_out=fopen(argv[2], "w")) == NULL) {
    fprintf(stderr, "Errore in apertura file %s\n", argv[1]);
    exit(1);
  }

  sem_init(&sem_read, 0, 1);
  sem_init(&sem_reverse, 0, 0);
  sem_init(&sem_write, 0, 0);

  pthread_create(&tid_read, NULL, read, NULL);
  pthread_create(&tid_reverse, NULL, reverse, NULL);
  pthread_create(&tid_write, NULL, write, NULL);

  pthread_join(tid_read, NULL);
  pthread_join(tid_reverse, NULL);
  pthread_join(tid_write, NULL);

  sem_destroy(&sem_read);
  sem_destroy(&sem_reverse);
  sem_destroy(&sem_write);

  fclose(fp_in);
  fclose(fp_out);

  return 0;
}

void *read(void *arg) {
  while (1) {
    sem_wait(&sem_read);

    if (fgets(buffer, MAX_CHAR, fp_in) == NULL) {
      end=1;
      sem_post(&sem_reverse);
      break;
    }

    sem_post(&sem_reverse);
  }

  pthread_exit((void *) 0);
}

void *reverse(void *arg) {
  int len;
  char tmp;

  while (1) {
    sem_wait(&sem_reverse);

    if (end) {
      sem_post(&sem_write);
      break;
    }

    len=strlen(buffer)-1;
    for (int i=0; i<((len-1)/2); i++) {
      tmp=buffer[i];
      buffer[i]=buffer[len-i-1];
      buffer[len-i-1]=tmp;
    }
    for (int i=0; i<len; i++) {
      if (isalpha(buffer[i])) {
        buffer[i]=toupper(buffer[i]);
      }
    }

    sem_post(&sem_write);
  }

  pthread_exit((void *) 0);
}

void *write(void *arg) {
  while (1) {
    sem_wait(&sem_write);

    if (end) {
      break;
    }

    fprintf(fp_out, "%s", buffer);

    sem_post(&sem_read);
  }

  pthread_exit((void *) 0);
}
