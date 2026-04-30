#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#define LIMITE 10

void calcula() {
    long long unsigned t;
    for(t = 0; t < (0xFFFFFF); t++);
}

pthread_t array[LIMITE];
int n = 0;

void *createThread();

int main(void) {
    pthread_create(&array[n], NULL, &createThread, NULL);
    pthread_join(array[n], NULL);
    return 0;
}

void *createThread() {
    printf("He nacido. Soy el hilo con ID %lu \n", pthread_self());

    n++;
    calcula();
    if(n < LIMITE) {
        pthread_create(&array[n], NULL, &createThread, NULL);
        pthread_join(array[n], NULL);
    } else {
        char g[10];
        fgets(g, sizeof(g), stdin);
    }
    pritnf("Soy el hilo con un ID %lu y acabo mi ejecucióm \n", pthread_self());
    return 0;
}