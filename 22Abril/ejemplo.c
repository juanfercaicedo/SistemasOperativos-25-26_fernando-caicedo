#include <stdio.h>
#include <pthread.h>

#define LIMITE 1000000

int variable_compartida = 0;

void* suma(void* arg) {
    for (int i = 0; i < LIMITE; i++) {
        variable_compartida += 1;
    }
    return NULL;
}

void* resta(void* arg) {
    for (int i = 0; i < LIMITE; i++) {
        variable_compartida -= 1;
    }
    return NULL;
}

int main(void) {

    pthread_t hilo1, hilo2;

    // Crear hilos
    pthread_create(&hilo1, NULL, &suma, NULL);
    pthread_create(&hilo2, NULL, &resta, NULL);

    pthread_join(hilo1, NULL);
    pthread_join(hilo2, NULL);

    printf("Valor final: %d\n", variable_compartida);

    return 0;
}