#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/syscall.h>

#define NUCLEOS_NECESARIOS 4


int volatile nucleosPlasma = 0;
int volatile mensaje = 0;

pid_t idNucleo;
pthread_t nucleo, monitor;

pthread_mutex_t lock;
pthread_cond_t nucleoInsertado;

void *hiloNucleo(void *arg){
    idNucleo = getpid();
    int TID = idNucleo;

    pthread_mutex_lock(&lock);

    while (nucleosPlasma < NUCLEOS_NECESARIOS) {
        printf("Ingresa núcleos para que funcione el reactor");
        // Mata el proceso si no tenemos los nucles necesarios
        pthread_cond_wait(&nucleoInsertado, &lock);

        if(mensaje){
            printf("Nucleo insertado, tienes %d de %d", nucleosPlasma, NUCLEOS_NECESARIOS);

            mensaje = 0;
        }

    }
    pthread_mutex_unlock(&lock);

    printf("Tienes los nucleos necesarios");

    return;
}

void *hiloMonitor(void *arg) {
    while(nucleosPlasma < NUCLEOS_NECESARIOS){
        sleep(2);
    }
    printf("Reactor inicializado exitosamente!!!");

    return NULL;
}

void manejadorSeñal(int signum) {
    nucleosPlasma++;
    mensaje = 1;

    pthread_cond_signal(&nucleoInsertado);
}


int main(void) {
    // Creamos señal SIGUSR1
    signal(SIGUSR1, manejadorSeñal);

    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&nucleoInsertado, NULL);

    pthread_create(&nucleo, NULL, hiloNucleo, NULL);
    pthread_create(&monitor, NULL, hiloMonitor, NULL);
    // Esperamos a que los hilos acaben 
    pthread_join(nucleo, NULL);
    pthread_join(monitor, NULL);

    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&nucleoInsertado);
    return 0;
}

