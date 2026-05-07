/*
Creamos dos hilos, un hilo manejará al otro utilizando mutex y señales
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <asm-generic/unistd.h>

void *hilo1_func();
void *hilo2_func();
void manejador(int);

pid_t id_hilo;
pthread_t hilo1, hilo2;
pthread_mutex_t lock;

int main(void)
{
    signal(SIGURG, manejador);                       // SIGURG es una señal que si tiene signficado en el Sistema operativo. Es nuestra forma de decir que algo urgente ha pasado.
    pthread_create(&hilo1, NULL, &hilo1_func, NULL); // Creamos los hilos
    pthread_create(&hilo2, NULL, &hilo2_func, NULL); // Creamos los hilos

    // Esperamos los hilos
    pthread_join(hilo1, NULL);
    pthread_join(hilo2, NULL);

    return 0;
}

void *hilo2_func()
{
    id_hilo = syscall(__NR_gettid);
    while (1)
    {
        printf("Soy el hilo 2: estoy trabajando\n");
        sleep(2);
    }
    return 0;
}

void *hilo1_func()
{
    while (1)
    {
        // Dejamos trabajor un rato al hilo 2
        sleep(5);
        puts("Vamos a parar al hilo 2");
        pthread_mutex_lock(&lock);
        kill(id_hilo, SIGURG);
        sleep(5);
        puts("Ponemos en marcha el hilo 2");
        pthread_mutex_unlock(&lock);
    }
    return 0;
}

void manejador(int signum)
{
    pthread_mutex_lock(&lock);
    pthread_unlock_unlock(&lock);
}