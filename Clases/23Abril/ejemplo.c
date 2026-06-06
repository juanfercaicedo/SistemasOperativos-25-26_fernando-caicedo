#include <stdio.h>
#include <pthread.h>

#define LIMITE 1000000

int variable_compartida;
pthread_t hilo1, hilo2;
pthread_mutex_t lock; // Siempre tiene un contador de 1, es como un cerojo 

void* suma(void* arg) {
    for (int i = 0; i < LIMITE; i++) {
        pthread_mutex_lock(&lock);
        variable_compartida += 1;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

void* resta(void* arg) {
    for (int i = 0; i < LIMITE; i++) {
        pthread_mutex_lock(&lock);
        variable_compartida -= 1;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main(void) {
    variable_compartida = 0;

    pthread_mutex_init(&lock, NULL);


    // Crear hilos
    pthread_create(&hilo1, NULL, &suma, NULL);
    pthread_create(&hilo2, NULL, &resta, NULL);

    pthread_join(hilo1, NULL);
    pthread_join(hilo2, NULL);

    printf("Valor final: %d\n", variable_compartida);

    pthread_mutex_destroy(&lock);

    return 0;
}