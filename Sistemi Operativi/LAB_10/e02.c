#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define N 3

void *monomio(void *arg);
void *polinomio(void *arg);

typedef struct line_s {
  float c, x;
  int n;
} line_t;

typedef struct thread_data_s {
  pthread_t tid;
  int id;
  const char *filename;
  int end;
  float result;
  sem_t sem;
} thread_data_t;

thread_data_t thread_data[N+1];

int main(int argc, char const *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Uso: %s fileIn\n", argv[0]);
    exit(1);
  }

  thread_data[0].id=0;
  thread_data[0].filename=NULL;
  thread_data[0].end=0;
  thread_data[0].result=0.0;
  sem_init(&(thread_data[0].sem), 0, 0);
  pthread_create(&(thread_data[0].tid), NULL, polinomio, (void *)&(thread_data[0].id));
  for (size_t i = 1; i <= N; i++) {
    thread_data[i].id=i;
    thread_data[i].filename=argv[1];
    thread_data[i].end=0;
    thread_data[i].result=0.0;
    sem_init(&(thread_data[i].sem), 0, 1);
    pthread_create(&(thread_data[i].tid), NULL, monomio, (void *)&(thread_data[i].id));
  }

  for (size_t i = 0; i <= N; i++) {
    pthread_join(thread_data[i].tid, NULL);
  }
  
  for (size_t i = 0; i <= N; i++) {
    sem_destroy(&(thread_data[i].sem));
  }

  return 0;
}

void *monomio(void *arg) {
  int id, fd, lines, offset;

  line_t line;

  id=*((int *) arg);

  fd=open(thread_data[id].filename, O_RDONLY);

  lines=0;
  while (1) {
    sem_wait(&thread_data[id].sem);

    offset=((lines*3)+id-1)*(sizeof(line));
    lseek(fd, offset, SEEK_SET);
    if (read(fd, &line, sizeof(line))) {
      thread_data[id].result=line.c;
      for (size_t i = 0; i < line.n; i++) {
        thread_data[id].result*=line.x;
      }
      thread_data[id].end=0;
    } else {
      thread_data[id].result=0;
      thread_data[id].end=1;
      sem_post(&thread_data[0].sem);
      break;
    }
    lines++;

    sem_post(&thread_data[0].sem);
  }

  close(fd);

  pthread_exit((void *) 0);
}

void *polinomio(void *arg) {
  while (1) {
    for (size_t i = 0; i < N; i++) {
      sem_wait(&thread_data[0].sem);
    }

    thread_data[0].result=0;
    for (size_t i = 1; i <= N; i++) {
      if (thread_data[i].end) {
        thread_data[0].end++;
      }
      thread_data[0].result+=thread_data[i].result;
    }

    if (thread_data[0].end == N) {
      break;
    }

    fprintf(stdout, "%f\n", thread_data[0].result);

    for (size_t i = 1; i <= N; i++) {
      sem_post(&thread_data[i].sem);
    }
  }

  pthread_exit((void *) 0);
}
