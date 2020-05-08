#include <stdio.h>
#include <stdlib.h>

int atomicIncrement(int *var) {
    int tmp = *var;
    *var = tmp + 1;
    return (tmp);
}

int ticketNumber, turnNumber;

void init(void) {
    ticketNumber=0;
    turnNumber=0;
}

void lock(void) {
    int myTurn=atomicIncrement(&ticketNumber);
    while (turnNumber != myTurn);
}

void unlock(void) {
    atomicIncrement(&turnNumber);
}

int main(int argc, char *argv[]) {
    return 0;
}
