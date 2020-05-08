#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define N 8
#define INDEX 'B'

sem_t *sem;

typedef struct threadArg {
    pthread_t tid;
    int id;
} threadArg_t;

static void *threadRoutine(void *arg) {
    threadArg_t *td=(threadArg_t *)arg;
    
    if (td->id == ('B'-INDEX)) {
        sem_wait(&(sem[td->id]));
        printf("B\n");
        sleep(1);
        sem_post(&(sem['I'-INDEX]));
    }
    
    if (td->id == ('C'-INDEX)) {
        sem_wait(&(sem[td->id]));
        printf("C\n");
        sleep(1);
        sem_post(&(sem['E'-INDEX]));
        sem_post(&(sem['F'-INDEX]));
    }
    
    if (td->id == ('D'-INDEX)) {
        sem_wait(&(sem[td->id]));
        printf("D\n");
        sleep(1);
        sem_post(&(sem['H'-INDEX]));
    }
    
    if (td->id == ('E'-INDEX)) {
        sem_wait(&(sem[td->id]));
        printf("E\n");
        sleep(1);
        sem_post(&(sem['G'-INDEX]));
    }
    
    if (td->id == ('F'-INDEX)) {
        sem_wait(&(sem[td->id]));
        printf("F\n");
        sleep(1);
        sem_post(&(sem['G'-INDEX]));
    }
    
    if (td->id == ('G'-INDEX)) {
        sem_wait(&(sem[td->id]));
        sem_wait(&(sem[td->id]));
        printf("G\n");
        sleep(1);
        sem_post(&(sem['I'-INDEX]));
    }
    
    if (td->id == ('H'-INDEX)) {
        sem_wait(&(sem[td->id]));
        printf("H\n");
        sleep(1);
        sem_post(&(sem['I'-INDEX]));
    }
    
    if (td->id == ('I'-INDEX)) {
        sem_wait(&(sem[td->id]));
        sem_wait(&(sem[td->id]));
        sem_wait(&(sem[td->id]));
        printf("I\n");
        sleep(1);
    }
    
    pthread_exit((void *)0);
}

int main(int argc, char *argv[]) {
    void *ret;
    threadArg_t *td=malloc(N*sizeof(threadArg_t));
    sem=malloc(N*sizeof(sem_t));

    while (1) {
        for (int i=0; i<N; i++) {
            td[i].id=i;
            sem_init(&(sem[i]), 0, 0);
            pthread_create(&(td[i].tid), NULL, threadRoutine, (void *)&td[i]);
        }
 
        printf("A\n");
        sleep(1);
        sem_post(&(sem['B'-'B']));
        sem_post(&(sem['C'-'B']));
        sem_post(&(sem['D'-'B']));
 
        for (int i=0; i<N; i++) {
            pthread_join(td[i].tid, &ret);
            sem_destroy(&(sem[i]));
        }
    }

    return 0;
}
