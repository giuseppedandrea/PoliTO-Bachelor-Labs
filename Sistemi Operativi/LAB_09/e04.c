#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define N 9
#define INDEX 'A'

sem_t *sem;

typedef struct threadArg {
    pthread_t tid;
    int id;
} threadArg_t;

void *threadRoutine(void *arg) {
    threadArg_t *td=(threadArg_t *)arg;

    while (1) {
        if (td->id == ('A'-INDEX)) {
            sem_wait(&(sem[td->id]));
            printf("A\n");
            sleep(1);
            sem_post(&(sem['B'-INDEX]));
            sem_post(&(sem['C'-INDEX]));
            sem_post(&(sem['D'-INDEX]));
        }
    
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
            sem_post(&(sem['A'-INDEX]));
        }
    }
    
    pthread_exit((void *)0);
}

int main(int argc, char *argv[]) {
    threadArg_t *td=malloc(N*sizeof(threadArg_t));
    sem=malloc(N*sizeof(sem_t));

    for (int i=0; i<N; i++) {
        td[i].id=i;
        sem_init(&(sem[i]), 0, 0);
        pthread_create(&(td[i].tid), NULL, threadRoutine, (void *)&td[i]);
        pthread_detach(td[i].tid);
    }
    
    sem_post(&sem['A'-INDEX]);
    
    pthread_exit((void *)0);
}
