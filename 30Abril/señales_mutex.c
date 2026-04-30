#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

void *hilo1_func();
void *hilo2_func();
void manejador(int);

pid_t id_hilo;
pthread_t hilo1, hilo2;
pthread_mutex_t lock;

int main(void) {
    signal(SIGURG, manejador);
    pthread_create(&hilo1, NULL, &hilo1_func; NULL);
    pthread_create(&hilo2, NULL, &hilo2_func; NULL);
    pthread_join(hilo1, NULL);
    pthread_join(hilo2, NULL);

    return 0;
}

void *hilo2_func() {
    printf("Soy el hilo 2: estoy trabajando\n");
    sleep(2);
}