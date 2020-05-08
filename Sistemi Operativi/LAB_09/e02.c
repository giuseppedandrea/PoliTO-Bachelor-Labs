#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void semaphoreInit(int *S) {
    if (pipe(S) == -1) {
        printf("Error\n");
        exit(1);
    }
    return;
}

void semaphoreWait(int *S) {
    char c;
    if (read(S[0], &c, sizeof(char)) != 1) {
        printf("Error\n");
        exit(1);
    }
    return;
}

void semaphoreSignal(int *S) {
    char c = 'X';
    if (write(S[1], &c, sizeof(char)) != 1) {
        printf("Error\n");
        exit(1);
    }
    return;
}

int main(int argc, char *argv[]) {
    int Sa[2], Sb[2], Sc[2], Sd[2], Se[2], Sf[2], Sg[2], Sh[2], Si[2];

    semaphoreInit(Sa);
    semaphoreInit(Sb);
    semaphoreInit(Sc);
    semaphoreInit(Sd);
    semaphoreInit(Se);
    semaphoreInit(Sf);
    semaphoreInit(Sg);
    semaphoreInit(Sh);
    semaphoreInit(Si);

    semaphoreSignal(Sa);
    
    while (1) {
        semaphoreWait(Sa);
        printf("A\n");
        sleep(1);
        semaphoreSignal(Sb);
        semaphoreSignal(Sc);
        semaphoreSignal(Sd);
        for (int i=1; i<=8; i++) {
            if (fork()==0) {
                char process = 'A'+i;
                if (process == 'B') {
                    semaphoreWait(Sb);
                    printf("B\n");
                    sleep(1);
                    semaphoreSignal(Si);
                }
                if (process == 'C') {
                    semaphoreWait(Sc);
                    printf("C\n");
                    sleep(1);
                    semaphoreSignal(Se);
                    semaphoreSignal(Sf);
                }
                if (process == 'D') {
                    semaphoreWait(Sd);
                    printf("D\n");
                    sleep(1);
                    semaphoreSignal(Sh);
                }
                if (process == 'E') {
                    semaphoreWait(Se);
                    printf("E\n");
                    sleep(1);
                    semaphoreSignal(Sg);
                }
                if (process == 'F') {
                    semaphoreWait(Sf);
                    printf("F\n");
                    sleep(1);
                    semaphoreSignal(Sg);
                }
                if (process == 'G') {
                    semaphoreWait(Sg);
                    semaphoreWait(Sg);
                    printf("G\n");
                    sleep(1);
                    semaphoreSignal(Si);
                }
                if (process == 'H') {
                    semaphoreWait(Sh);
                    printf("H\n");
                    sleep(1);
                    semaphoreSignal(Si);
                }
                if (process == 'I') {
                    semaphoreWait(Si);
                    semaphoreWait(Si);
                    semaphoreWait(Si);
                    printf("I\n");
                    semaphoreSignal(Sa);
                }
                exit(0);
            }        
        }        
    }

    return 0;
}
