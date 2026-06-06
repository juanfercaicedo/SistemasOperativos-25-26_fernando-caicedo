#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t fibonacci, primo;

void* sucesionFibonacci(void *arg) {
    int n = *(int*)arg;
    int a = 0, b = 1, siguiente;

    pthread_mutex_lock(&fibonacci);

    for (int i = 0; i < n; i++) {
        printf("%d ", a);
        siguiente = a + b;
        a = b;
        b = siguiente;
    }
    printf("\n");

    pthread_mutex_unlock(&fibonacci);
    return NULL;
}

void* numeroPrimo(void *arg) {
    int n = *(int*)arg;
    int esPrimo = 1;

    if (n <= 1) esPrimo = 0;

    for (int i = 2; i <= n/2; i++) {
        if (n % i == 0) {
            esPrimo = 0;
            break;
        }
    }

    pthread_mutex_lock(&primo);

    if (esPrimo)
        printf("El número %d es primo\n", n);
    else
        printf("El número %d no es primo\n", n);

    pthread_mutex_unlock(&primo);
    return NULL;
}

int main(void) {
    pthread_mutex_init(&fibonacci, NULL);
    pthread_mutex_init(&primo, NULL);

    int numeroUsuario;
    printf("Introduce un número: ");
    scanf("%d", &numeroUsuario);

    pthread_t hiloFibonacci, hiloPrimo;
    pthread_create(&hiloFibonacci, NULL, sucesionFibonacci, &numeroUsuario);
    pthread_create(&hiloPrimo, NULL, numeroPrimo, &numeroUsuario);

    pthread_join(hiloFibonacci, NULL);
    pthread_join(hiloPrimo, NULL);

    pthread_mutex_destroy(&fibonacci);
    pthread_mutex_destroy(&primo);

    return 0;
}
